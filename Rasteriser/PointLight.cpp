#include "pch.h"
#include "PointLight.h"
#include <algorithm>
#include <cmath>

PointLight::PointLight(const Vector3f& position, const Vector3f& ambient, float shininess) : Light(position, ambient, shininess) {}

Vector3f reflect(const Vector3f& I, const Vector3f&);


Vector3f PointLight::calculate(const Vertex& vertex) const
{
	Vector3f lightVector = Vector3f(position - vertex.position).normalized();

	Vector3f normalizedVertPos = vertex.position.normalized();

	Vector3f reflected = reflect(lightVector, vertex.normal);

	Vector3f diffuse = lightVector.dotProduct(vertex.normal);

	Vector3f specular = pow(reflected.dotProduct(normalizedVertPos), shininess);

	/*Vector3f diffuse = Vector3f(std::max({ 0.0f, vertex.normal.dotProduct(lightVector) }));

	float specular = vertex.normal.dotProduct(lightVector);
	specular = pow(specular, shininess);*/

	return { ambient + diffuse + specular };
}

Vector3f reflect(const Vector3f& I, const Vector3f& N)
{
	Vector3f ret = I - (N * N.dotProduct(I) * 2.0f);

	return ret;
}
