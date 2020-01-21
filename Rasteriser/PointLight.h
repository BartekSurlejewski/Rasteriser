#pragma once
#include "Light.h"
class PointLight : public Light
{
public:
	PointLight(const Vector3f& position, const Vector3f& ambient, float shininess);
	Vector3f calculate(const Vertex& vertex) const override;
};

