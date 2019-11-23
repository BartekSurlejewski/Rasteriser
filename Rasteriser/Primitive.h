#pragma once
#include <vector>
#include <memory>
#include "Triangle.h"

class Primitive
{
public:
	Primitive(std::vector<std::shared_ptr<Triangle>> triangles);
	Primitive() = default;

	std::vector<std::shared_ptr<Triangle>> getTriangles() const;
	
protected:
	std::vector<std::shared_ptr<Triangle>> triangles;
};

