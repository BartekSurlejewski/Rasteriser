#pragma once
#include <vector>
#include "Triangle.h"
#include "Transform.h"

class Mesh
{
public:
	Mesh();
	Mesh(std::string filename, const Vector3f& color);
	Mesh(std::vector<Triangle*> triangles);

	std::vector<Triangle*> getFaces() const;
	void setFaces(const std::vector<Triangle*>& faces);
	Transform* getTransform();

	bool loadObjFile(std::string filename, const Vector3f& color);
	
protected:
	Transform transform;
	std::vector<Triangle*> faces;
};

