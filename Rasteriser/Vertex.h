#pragma once
#include "Vector3.h"

struct Vertex
{
	Vertex(const Vector3f& position, const Vector3f& color);
	Vertex(const Vertex& other);
	Vertex() = default;
	Vertex& operator=(const Vertex& other);

	Vector3f position;
	Vector3f color;
};

