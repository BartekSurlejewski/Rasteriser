#pragma once
#include <vector>
#include <memory>
#include "Triangle.h"

class Primitive
{
public:
	Primitive(const std::vector<Triangle>& triangles);
	Primitive() = default;

	std::vector<Triangle> getTriangles() const;
	
protected:
	std::vector<Triangle> triangles;
};

