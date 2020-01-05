#pragma once
#include <vector>
#include "Mesh.h"
#include <memory>

class Scene
{
public:
	std::vector<std::shared_ptr<Mesh>> getPrimitives() const;
	void addPrimitive(const Mesh& primitive);

private:
	std::vector<std::shared_ptr<Mesh>> primitives;
};

