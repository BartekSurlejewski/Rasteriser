#pragma once
#include <vector>
#include "Triangle.h"
#include "Transform.h"

class Mesh
{
public:
	Mesh(std::vector<Triangle*> triangles);

	std::vector<Triangle*> getTriangles() const;
	Transform* getTransform();

	bool LoadObjFile(std::string filename, const Vector3f& color);
	
protected:
	Transform transform;
	std::vector<Triangle*> triangles;
};

