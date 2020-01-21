#include "pch.h"
#include "Triangle.h"
#include "Vector2.h"
#include "Vector4.h"

Triangle::Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, bool normalsCalculated) : v0(Vertex(v0)),
v1(Vertex(v1)),
v2(Vertex(v2))
{
	if(!normalsCalculated)
	{
		Vector3f normal = (v2.position - v0.position).crossProduct(v1.position - v0.position).normalized();

		this->v0.normal = normal;
		this->v1.normal = normal;
		this->v2.normal = normal;
	}
}

Triangle::Triangle(const Triangle& other) : v0(other.v0), v1(other.v1), v2(other.v2), color(other.color) {}

Triangle& Triangle::operator=(const Triangle& other)
{
	v0 = other.v0;
	v1 = other.v1;
	v2 = other.v2;
	color = other.color;

	return *this;
}

Triangle::Triangle() {}
