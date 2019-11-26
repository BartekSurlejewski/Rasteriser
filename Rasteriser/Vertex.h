#pragma once
#include "Vector3.h"
#include <memory>

struct Vertex
{
	Vertex(const Vector3f& position, const Vector3f& color);
	Vertex() = default;
	Vertex(const Vertex& other);
	Vertex& operator=(const Vertex& other);

	Vector3f position;
	Vector3f color;
};

