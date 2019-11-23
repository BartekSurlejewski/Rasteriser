#pragma once
#include <vector>
#include "Primitive.h"
#include <memory>

class Scene
{
public:
	Scene() = default;
	
	std::vector<std::shared_ptr<Primitive>> getPrimitives() const;
	void addPrimitive(const Primitive& primitive);

private:
	std::vector<std::shared_ptr<Primitive>> primitives;
};

