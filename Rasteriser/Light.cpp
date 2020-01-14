#include "pch.h"
#include "Light.h"

Light::Light(const Vector3f& position, const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular,
	float shininess) : position(position),
	ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	shininess(shininess) {}
