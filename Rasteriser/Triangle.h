#pragma once
#include "Vertex.h"

struct Triangle
{
	Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, bool normalsCalculated);
	Triangle(const Triangle& other);
	Triangle& operator=(const Triangle& other);
	Triangle();
	
	Vertex v0;
	Vertex v1;
	Vertex v2;
	Vector3f color = Vector3f(1, 0, 0);
};
