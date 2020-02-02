#pragma once
#include <vector>
#include "Mesh.h"
#include <memory>

class Scene
{
public:

	std::vector<Mesh*>& getPrimitives();
	void addPrimitive(Mesh& primitive);

private:
	std::vector<Mesh*> primitives;
};

