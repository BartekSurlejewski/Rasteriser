#pragma once
#include <vector>
#include "Mesh.h"
#include <memory>

class Scene
{
public:
	Scene& operator=(const Scene& other);
	
	std::vector<Mesh*> getPrimitives() const;
	void addPrimitive(Mesh& primitive);

private:
	std::vector<Mesh*> primitives;
};

