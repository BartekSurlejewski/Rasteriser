#include "pch.h"
#include "Rasteriser.h"
#include <algorithm>

Rasteriser::Rasteriser(const Scene& scene, std::shared_ptr<Image>& image) : scene(std::make_shared<Scene>(scene)), image(image), imageWidth(image->getWidth()), imageHeight(image->getHeight()) {}

void Rasteriser::print() const
{
	std::vector<std::shared_ptr<Primitive>> primitives = scene->getPrimitives();

	for (unsigned int i = 0; i < primitives.size(); i++)
	{
		const std::shared_ptr<Primitive> primitive = primitives[i];
		const std::vector<Triangle> triangles = primitive->getTriangles();

		for (unsigned int j = 0; j < triangles.size(); j++)
		{
			// STEP I: project vertices of the triangle using perspective projection
			Triangle triangle = triangles[j];
			Vector3f v0 = orthogonalProject(triangle.v0.position);
			Vector3f v1 = orthogonalProject(triangle.v1.position);
			Vector3f v2 = orthogonalProject(triangle.v2.position);

			float minx = std::min({ v0.x, v1.x, v2.x, 0.0f });
			float maxx = std::max({ v0.x, v1.x, v2.x, imageWidth - 1.0f });
			float miny = std::min({ v0.y, v1.y, v2.y, 0.0f });
			float maxy = std::max({ v0.y, v1.y, v2.y, imageHeight - 1.0f });

			// STEP II: is this pixel contained in the projected image of the triangle?
			for (unsigned int x = minx; x < maxx; x++)
			{
				for (unsigned int y = miny; y < maxy; y++)
				{
					if (pixelContainedIn2DTriangle(v0, v1, v2, x, y))
					{
						image->writePixel(x, y, triangle.color);
					}
				}
			}
		}
	}
}

Vector3f Rasteriser::orthogonalProject(const Vector3f& vertex) const
{
	return { (vertex.x + 1) * imageWidth * 0.5f, (vertex.y + 1) * imageHeight * 0.5f, vertex.z };
}

bool Rasteriser::pixelContainedIn2DTriangle(const Vector3f& vertex0, const Vector3f& vertex1, const Vector3f& vertex2,
	unsigned pixelX, unsigned pixelY) const
{
	float dx12 = vertex0.x - vertex1.x;
	float dx23 = vertex1.x - vertex2.x;
	float dx31 = vertex2.x - vertex1.x;
	float dy12 = vertex0.y - vertex1.y;
	float dy23 = vertex1.y - vertex2.y;
	float dy31 = vertex2.y - vertex0.y;

	bool straight0 = dx12 * (pixelY - vertex0.y) - dy12 * (pixelX - vertex0.x) > 0;
	bool straight1 = dx23 * (pixelY - vertex1.y) - dy23 * (pixelX - vertex1.x) > 0;
	bool straight2 = dx31 * (pixelY - vertex2.y) - dy31 * (pixelX - vertex2.x) > 0;

	return (straight0 && straight1 && straight2);
}
