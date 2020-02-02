#include "pch.h"
#include "PointLight.h"
#include <algorithm>
#include <cmath>

PointLight::PointLight(const Vector3f& position, const Vector3f& ambient, float shininess) : Light(position, ambient, shininess) {}

Vector3f reflect(const Vector3f& I, const Vector3f&);

inline Vector3f PointLight::calculate(const Vertex& vertex) const
{
	Vector3f lightVector(Vector3f(position - vertex.position).normalized());
	Vector3f normalizedVertPos(vertex.position.normalized());
	Vector3f reflected(reflect(lightVector, vertex.normal));
	Vector3f diffuse(lightVector.dotProduct(vertex.normal));
	Vector3f specular(pow(reflected.dotProduct(normalizedVertPos), shininess));
	Vector3f color(ambient + diffuse + specular);
	
	if (color.x > 1) color.x = 1;
	if (color.y > 1) color.y = 1;
	if (color.z > 1) color.z = 1;

	if (color.x < 0) color.x = 0;
	if (color.y < 0) color.y = 0;
	if (color.z < 0) color.z = 0;

	return color;
}

inline Vector3f reflect(const Vector3f& I, const Vector3f& N)
{
	return I - (N * N.dotProduct(I) * 2.0f);
}
