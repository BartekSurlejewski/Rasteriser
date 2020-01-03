#pragma once
#include <vector>
#include "Triangle.h"
#include "Transform.h"


class Model
{
public:
	Model(std::vector<Triangle*> triangles);

	std::vector<Triangle*> getTriangles() const;
	Vector3f getPosition() const;
	Vector3f getRotation() const;
	Vector3f getScale() const;

	void setPosition(const Vector3f& newPosition);
	void setRotation(const Vector3f& newRotation);
	void setScale(const Vector3f& newScale);
	
protected:
	Transform transform;
	std::vector<Triangle*> triangles;
};

