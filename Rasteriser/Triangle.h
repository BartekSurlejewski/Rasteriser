#pragma once
#include <vector>
#include "Vector3.h"

class Triangle
{
public:
	Triangle(Vector3f& x, Vector3f& y, Vector3f& z, Vector3f& color);

	Vector3f& v0;
	Vector3f& v1;
	Vector3f& v2;
	Vector3f& color;
};

