#include "pch.h"
#include "Primitive.h"
#include <utility>

Primitive::Primitive(std::vector<std::shared_ptr<Triangle>> triangles) : triangles(std::move(triangles)) {}

std::vector<std::shared_ptr<Triangle>> Primitive::getTriangles() const
{
	return triangles;
}
