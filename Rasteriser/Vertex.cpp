#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(const Vector3f& position, const Vector3f& color) : position(position), color(color) {}
Vertex::Vertex(const Vertex& other) : Vertex(other.position, other.color) {}
Vertex& Vertex::operator=(const Vertex& other)
{
	position = other.position;
	color = other.color;
	
	return *this;
}
