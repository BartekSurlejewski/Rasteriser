#include "pch.h"
#include "Triangle.h"

Triangle::Triangle(const std::vector<Vector3f>& vertices) : vertices(vertices) {}

std::vector<Vector3f> Triangle::getVertices() const
{
	return vertices;
}
