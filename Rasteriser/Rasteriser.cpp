#include "pch.h"
#include "Rasteriser.h"
#include <algorithm>
#include <iostream>
#include "Vector2.h"

Rasteriser::Rasteriser(Scene& scene, std::shared_ptr<Image>& image) : scene(&scene),
image(image), imageWidth(image->getWidth()),
imageHeight(image->getHeight())
{
	depthBuffer = new float*[imageWidth];

	for (unsigned int i = 0; i < imageWidth; i++)
	{
		depthBuffer[i] = new float[imageHeight];
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

void Rasteriser::print(const Camera& camera)
{
	std::vector<Mesh*> models = scene->getPrimitives();

	for (unsigned int i = 0; i < models.size(); i++)
	{
		const Mesh* primitive = models[i];
		const std::vector<Triangle*> triangles = primitive->getFaces();
		Transform* transform = &primitive->getTransform();

		Matrix4x4f wvp = Matrix4x4f::Identity();
		//wvp *= transform->getWorldMatrix();
		//wvp *= camera.getViewMatrix();
		//wvp *= camera.getProjectionMatrix();

		wvp *= camera.getProjectionMatrix();
		wvp *= camera.getViewMatrix();
		wvp *= transform->getWorldMatrix();

		for (unsigned int j = 0; j < triangles.size(); j++)
		{
			// STEP I: project vertices of the triangle using perspective projection
			Triangle* triangle = triangles[j];

			Vector3f vx = orthogonalProject(triangle->v0.position);
			Vector3f vy = orthogonalProject(triangle->v1.position);
			Vector3f vz = orthogonalProject(triangle->v2.position);
			
			Vector4f v0 = wvp * vx;
			Vector4f v1 = wvp * vy;
			Vector4f v2 = wvp * vz;

			v0 /= v0.w;
			v1 /= v1.w;
			v2 /= v2.w;

			std::cout << "vx: " << vx << "vy: " << vy << "vz: " << vz << std::endl;
			std::cout << "v0: " << v0 << "v1: " << v1 << "v2: " << v2 << std::endl;

			float minx = std::min({ v0.x, v1.x, v2.x });
			float maxx = std::max({ v0.x, v1.x, v2.x });
			float miny = std::min({ v0.y, v1.y, v2.y });
			float maxy = std::max({ v0.y, v1.y, v2.y });

			minx = std::max({ minx, 0.0f });
			maxx = std::min({ maxx, imageWidth - 1.0f });
			miny = std::max({ miny, 0.0f });
			maxy = std::min({ maxy, imageHeight - 1.0f });

			// STEP II: is this pixel contained in the projected image of the triangle?
			for (unsigned int x = (unsigned int)minx; x < maxx; x++)
			{
				for (unsigned int y = (unsigned int)miny; y < maxy; y++)
				{
					float area = edgeFunction(
						v0, v1, { static_cast<unsigned int>(v2.x), static_cast<unsigned int>(v2.y) });
					// area of the triangle multiplied by 2 
					float lambda0 = edgeFunction(v1, v2, { x, y }); // signed area of the triangle v1v2p multiplied by 2 
					float lambda1 = edgeFunction(v2, v0, { x, y }); // signed area of the triangle v2v0p multiplied by 2 
					float lambda2 = edgeFunction(v0, v1, { x, y }); // signed area of the triangle v0v1p multiplied by 2 

					// if point p is inside triangles defined by vertices v0, v1, v2
					if (lambda0 >= 0 && lambda1 >= 0 && lambda2 >= 0)
					{
						// barycentric coordinates are the areas of the sub-triangles divided by the area of the main triangle
						lambda0 /= area;
						lambda1 /= area;
						lambda2 /= area;

						const float depth = lambda0 * v0.z + lambda1 * v1.z + lambda2 * v2.z;

						if (depth < depthBuffer[x][y])
						{
							Vector3f color = lambda0 * triangle->v0.color + lambda1
								* triangle->v1.color + lambda2 * triangle->v2.color;

							image->writePixel(x, y, color);
							depthBuffer[x][y] = depth;
						}
					}
				}
			}
		}
	}
}

inline Vector3f Rasteriser::orthogonalProject(const Vector3f& vertex) const
{
	return { (vertex.x + 1) * imageWidth * 0.5f, imageHeight - (vertex.y + 1) * imageHeight * 0.5f, vertex.z };
}

inline float Rasteriser::edgeFunction(const Vector3f& a, const Vector3f& b, const Vector2<unsigned int>& c) const
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

inline float Rasteriser::edgeFunction(const Vector4f& a, const Vector4f& b, const Vector2<unsigned>& c) const
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}
