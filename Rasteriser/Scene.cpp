#include "pch.h"
#include "Scene.h"

std::vector<std::shared_ptr<Mesh>> Scene::getPrimitives() const
{
	return primitives;
}

void Scene::addPrimitive(const Mesh& primitive)
{
	primitives.push_back(std::make_shared<Mesh>(primitive));
}
