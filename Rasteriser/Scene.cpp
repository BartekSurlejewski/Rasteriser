#include "pch.h"
#include "Scene.h"

std::vector<std::shared_ptr<Primitive>> Scene::getPrimitives() const
{
	return primitives;
}

void Scene::addPrimitive(const Primitive& primitive)
{
	primitives.push_back(std::make_shared<Primitive>(primitive));
}
