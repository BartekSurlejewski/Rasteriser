#include "pch.h"
#include "Scene.h"

Scene& Scene::operator=(const Scene& other)
{
	primitives = other.getPrimitives();

	return *this;
}

std::vector<Mesh*> Scene::getPrimitives() const
{
	return primitives;
}

void Scene::addPrimitive(Mesh& primitive)
{
	primitives.push_back(&primitive);
}
