#pragma once
#include "Vector3.h"
#include "Vertex.h"

class Light
{
public:
	Light(const Vector3f& position, const Vector3f& ambient, float shininess);

	virtual Vector3f calculate(const Vertex& vertex) const = 0;

protected:
	Vector3f position;
	Vector3f ambient;
	float shininess;
};