#pragma once
#include <vector>
#include "Primitive.h"
#include <memory>

class Scene
{
public:
	Scene() = default;
	
	std::vector<Primitive> getPrimitives() const;

private:
	std::vector<Primitive> primitives;
};

