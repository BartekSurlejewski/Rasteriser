#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(const Vector3f& position, const Vector3f& color, const Vector3f& normal) : position(position), color(color), normal(normal) {}
Vertex::Vertex(const Vertex& other) : Vertex(other.position, other.color, other.normal) {}
Vertex& Vertex::operator=(const Vertex& other)
{
	position = other.position;
	normal = other.normal;
	color = other.color;

	return *this;
}
