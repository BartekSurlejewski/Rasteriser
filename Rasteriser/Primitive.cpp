#include "pch.h"
#include "Primitive.h"
#include <utility>

Primitive::Primitive(std::vector<Triangle> triangles) : triangles(triangles) {}

std::vector<Triangle> Primitive::getTriangles() const
{
	return triangles;
}
