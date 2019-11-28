#pragma once
#include "Vertex.h"
#include "Vector2.h"

struct Triangle
{
	Triangle(const Vector3f& x, const Vector3f& y, const Vector3f& z, const Vector3f& color);
	Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	Triangle(const Triangle& other);
	Triangle& operator=(const Triangle& other);
	
	Vertex v0;
	Vertex v1;
	Vertex v2;
	Vector3f color = Vector3f(1, 0, 0);
};
