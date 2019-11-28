#include "pch.h"
#include "Triangle.h"
#include "Vector2.h"
#include "Vector4.h"

Triangle::Triangle(const Vector3f& x, const Vector3f& y, const Vector3f& z, const Vector3f& color) :
	v0(Vertex(x, color)), v1(Vertex(y, color)), v2(Vertex(z, color)),
	color(Vector3f(color)) {}

Triangle::Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2) : v0(Vertex(v0)),
                                                                           v1(Vertex(v1)),
                                                                           v2(Vertex(v2)) {}

Triangle::Triangle(const Triangle& other) : v0(other.v0), v1(other.v1), v2(other.v2), color(other.color) {}

Triangle& Triangle::operator=(const Triangle& other)
{
	v0 = other.v0;
	v1 = other.v1;
	v2 = other.v2;
	color = other.color;

	return *this;
}
