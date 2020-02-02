#include "pch.h"
#include "Rasteriser.h"
#include <algorithm>
#include <iostream>
#include "Vector2.h"
#include "Settings.h"
#include "PointLight.h"
#include <new>

Rasteriser::Rasteriser(Scene& scene, std::shared_ptr<Image>& image) : scene(&scene),
image(image), imageWidth(image->getWidth()),
imageHeight(image->getHeight())
{
	depthBuffer = new (std::nothrow) float*[imageWidth];

	for (unsigned int i = 0; i < imageWidth; i++)
	{
		depthBuffer[i] = new (std::nothrow) float[imageHeight];
		for (unsigned j = 0; j < imageHeight; j++)
		{
			depthBuffer[i][j] = 256;
		}
	}
}

Rasteriser::~Rasteriser()
{
	for (int i = 0; i < imageWidth; i++)
	{
		delete[] depthBuffer[i];
	}
	delete[] depthBuffer;
}

Vector3f tr(Matrix4x4f& world, Matrix4x4f& view, Matrix4x4f& projection, const Vector3f& vertexPosition)
{
	Vector4f vec{ vertexPosition, 1.0f };
	vec = world * vec;
	vec = view * vec;
	vec = projection * vec;
	vec /= vec.w;
	return Vector3f{ vec.x, vec.y, vec.z };
}

void Rasteriser::print(Camera& camera) const noexcept
{
	PointLight pointLight({ 1, -1.5, 1.0f }, { 0.2 }, 10);
	const std::vector<Mesh*>& models = scene->getPrimitives();

	for (unsigned int i = 0; i < models.size(); i++)
	{
		Mesh* primitive = models[i];
		const std::vector<Triangle>& triangles = primitive->getFaces();
		Transform& transform = primitive->getTransform();

		Matrix4x4f w = transform.getWorldMatrix();
		Matrix4x4f v = camera.getViewMatrix();
		Matrix4x4f p = camera.getProjectionMatrix();

		for (unsigned int j = 0; j < triangles.size(); j++)
		{
			// STEP I: project vertices of the triangle using perspective projection
			Triangle triangle = triangles[j];

			Vertex& vert0 = triangle.v0;
			Vertex& vert1 = triangle.v1;
			Vertex& vert2 = triangle.v2;

#if LIGHTING
			vert0.normal = w * vert0.normal;
			vert1.normal = w * vert1.normal;
			vert2.normal = w * vert2.normal;

			vert0.color = pointLight.calculate(vert0);
			vert1.color = pointLight.calculate(vert1);
			vert2.color = pointLight.calculate(vert2);
#else
			vert0.color = { 1, 0, 0 };
			vert1.color = { 0, 1, 0 };
			vert2.color = { 0, 0, 1 };
#endif
			
			const Vector3f& tmp0 = tr(w, v, p, vert0.position);
			const Vector3f& tmp1 = tr(w, v, p, vert1.position);
			const Vector3f& tmp2 = tr(w, v, p, vert2.position);

			const Vector3f& v0 = computeScreenCoordinates(tmp0);
			const Vector3f& v1 = computeScreenCoordinates(tmp1);
			const Vector3f& v2 = computeScreenCoordinates(tmp2);

			const Vector3f edge0 = v2 - v1;
			const Vector3f edge1 = v0 - v2;
			const Vector3f edge2 = v1 - v0;

			float minx = std::min({ v0.x, v1.x, v2.x });
			float maxx = std::max({ v0.x, v1.x, v2.x });
			float miny = std::min({ v0.y, v1.y, v2.y });
			float maxy = std::max({ v0.y, v1.y, v2.y });

			minx = std::max({ minx, 0.0f });
			maxx = std::min({ maxx, imageWidth - 1.0f });
			miny = std::max({ miny, 0.0f });
			maxy = std::min({ maxy, imageHeight - 1.0f });

			const float& area = edgeFunction(v0, v1, v2);

			// STEP II: is this pixel contained in the projected image of the triangle?
			for (unsigned int x = (unsigned int)minx; x <= maxx; x++)
			{
				for (unsigned int y = (unsigned int)miny; y <= maxy; y++)
				{
					Vector2<unsigned int> pixelSample(x + 0.5, y + 0.5);

					// area of the triangle multiplied by 2 
					float lambda0 = edgeFunction(v1, v2, pixelSample); // signed area of the triangle v1v2p multiplied by 2 
					float lambda1 = edgeFunction(v2, v0, pixelSample); // signed area of the triangle v2v0p multiplied by 2 
					float lambda2 = edgeFunction(v0, v1, pixelSample); // signed area of the triangle v0v1p multiplied by 2

					bool overlaps = true;

					overlaps &= (lambda0 == 0 ? ((edge0.y == 0 && edge0.x > 0) || edge0.y > 0) : (lambda0 > 0));
					overlaps &= (lambda1 == 0 ? ((edge1.y == 0 && edge1.x > 0) || edge1.y > 0) : (lambda1 > 0));
					overlaps &= (lambda2 == 0 ? ((edge2.y == 0 && edge2.x > 0) || edge2.y > 0) : (lambda2 > 0));

					// if point p is inside triangles defined by vertices v0, v1, v2
					if (overlaps)
					{
						// barycentric coordinates are the areas of the sub-triangles divided by the area of the main triangle
						lambda0 /= area;
						lambda1 /= area;
						lambda2 /= area;

						float depth = lambda0 * v0.z + lambda1 * v1.z + lambda2 * v2.z;
						depth = 1 / depth;

						if (depth < depthBuffer[x][y])
						{
							Vector3f color = lambda0 * vert0.color + lambda1
								* vert1.color + lambda2 * vert2.color;

							image->writePixel(x, y, color);

							depthBuffer[x][y] = depth;
						}
					}
				}
			}
		}
	}
}

inline Vector3f Rasteriser::computeScreenCoordinates(const Vector3f& vertex) const
{
	return { (vertex.x + 1) * imageWidth * 0.5f, (1 - vertex.y) / 2 * imageHeight, vertex.z };
}

inline float Rasteriser::edgeFunction(const Vector3f& a, const Vector3f& b, const Vector2<unsigned int>& c) const
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

inline float Rasteriser::edgeFunction(const Vector3f& a, const Vector3f& b, const Vector3f& c) const
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}