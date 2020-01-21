#include "pch.h"
#include "PointLight.h"
#include <algorithm>
#include <cmath>

PointLight::PointLight(const Vector3f& position, const Vector3f& ambient, float shininess) : Light(position, ambient, shininess) {}

Vector3f PointLight::calculate(const Vertex& vertex) const
{
	Vector3f lightVector = Vector3f(position - vertex.position).normalized();

	Vector3f diffuse = Vector3f(std::max({ 0.0f, vertex.normal.dotProduct(lightVector) })) * ambient;

	float specular = vertex.normal.dotProduct(lightVector);
	specular = pow(specular, shininess);

	return { diffuse + Vector3f(specular) };
}
