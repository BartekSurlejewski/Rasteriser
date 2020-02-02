#include "pch.h"
#include "Mesh.h"
#include <strstream>
#include "OBJLoader.h"
#include <new>

Mesh::Mesh(const std::string& filename, const Vector3f& color)
{
	OBJLoader* loader = new (std::nothrow) OBJLoader();
	loader->loadMesh(filename, *this, true, color);
	delete loader;
}
Mesh::Mesh(const std::vector<Triangle>& faces) : faces(faces) {}

std::vector<Triangle>& Mesh::getFaces()
{
	return faces;
}

void Mesh::setFaces(const std::vector<Triangle>& faces)
{
	this->faces = faces;
}

Transform& Mesh::getTransform()
{
	return transform;
}
