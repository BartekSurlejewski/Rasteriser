#pragma once
#include <vector>
#include "Triangle.h"
#include "Transform.h"

class Model
{
public:
	Model(std::vector<Triangle*> triangles);

	std::vector<Triangle*> getTriangles() const;
	Transform* getTransform();
	
protected:
	Transform transform;
	std::vector<Triangle*> triangles;
};

