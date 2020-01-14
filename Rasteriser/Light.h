#pragma once
#include "Vector3.h"

class Light
{
public:
	Light(const Vector3f& position, const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular,
		float shininess);

	virtual Vector3f calculate() const = 0;

private:
	Vector3f position;
	Vector3f ambient;
	Vector3f diffuse;
	Vector3f specular;
	float shininess;
};

