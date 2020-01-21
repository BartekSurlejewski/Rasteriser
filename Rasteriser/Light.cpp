#include "pch.h"
#include "Light.h"

Light::Light(const Vector3f& position, const Vector3f& ambient, float shininess) : position(position),
ambient(ambient),
shininess(shininess) {}
