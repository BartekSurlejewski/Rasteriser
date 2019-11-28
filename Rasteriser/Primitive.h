#pragma once
#include <vector>
#include "Triangle.h"

class Primitive
{
public:
	Primitive(std::vector<Triangle*> triangles);

	std::vector<Triangle*> getTriangles() const;
	
protected:
	std::vector<Triangle*> triangles;
};

