#pragma once
#include <vector>
#include "Triangle.h"
#include "Transform.h"

class Mesh
{
public:
	Mesh();
	Mesh(const std::string& filename, const Vector3f& color);
	explicit Mesh(const std::vector<Triangle>& faces);

	std::vector<Triangle>& getFaces();
	void setFaces(const std::vector<Triangle>& faces);
	Transform& getTransform();
	
protected:
	Transform transform;
	std::vector<Triangle> faces;
};

