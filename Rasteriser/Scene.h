#pragma once
#include <vector>
#include "Model.h"
#include <memory>

class Scene
{
public:
	std::vector<std::shared_ptr<Model>> getPrimitives() const;
	void addPrimitive(const Model& primitive);

private:
	std::vector<std::shared_ptr<Model>> primitives;
};

