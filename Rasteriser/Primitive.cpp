#include "pch.h"
#include "Primitive.h"

Primitive::Primitive(const std::vector<Triangle>& triangles) : triangles(triangles) {}

std::vector<Triangle> Primitive::getTriangles() const
{
	return triangles;
}
