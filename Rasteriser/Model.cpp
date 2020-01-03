#include "pch.h"
#include "Model.h"

Model::Model(std::vector<Triangle*> triangles) : triangles(std::move(triangles)) {}

std::vector<Triangle*> Model::getTriangles() const
{
	return triangles;
}
