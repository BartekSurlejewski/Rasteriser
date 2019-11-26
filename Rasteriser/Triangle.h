#pragma once
#include "Vector3.h"
#include "Vertex.h"

struct Triangle
{
	Triangle(const Vector3f& x, const Vector3f& y, const Vector3f& z, const Vector3f& color);
	Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	Triangle() = default;
	Triangle(const Triangle& other);
	Triangle& operator=(const Triangle& other);

	Vertex v0;
	Vertex v1;
	Vertex v2;
	Vector3f color;
};
