#pragma once
#include <vector>
#include "Vector3.h"

class Triangle
{
public:
	Triangle(const std::vector<Vector3f>& vertices);

	std::vector<Vector3f> getVertices() const;

private:
	std::vector<Vector3f> vertices;
};

