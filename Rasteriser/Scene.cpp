#include "pch.h"
#include "Scene.h"

std::vector<std::shared_ptr<Model>> Scene::getPrimitives() const
{
	return primitives;
}

void Scene::addPrimitive(const Model& primitive)
{
	primitives.push_back(std::make_shared<Model>(primitive));
}
