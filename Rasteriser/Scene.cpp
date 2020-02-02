#include "pch.h"
#include "Scene.h"

std::vector<Mesh*>& Scene::getPrimitives()
{
	return primitives;
}

void Scene::addPrimitive(Mesh& primitive)
{
	primitives.push_back(&primitive);
}
