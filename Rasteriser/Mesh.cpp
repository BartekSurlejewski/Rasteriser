#include "pch.h"
#include "Mesh.h"
#include <fstream>
#include <strstream>
#include "OBJLoader.h"

Mesh::Mesh(std::string filename, const Vector3f& color)
{
	OBJLoader* loader = new OBJLoader();
	loader->loadMesh(filename, *this, false);
	delete loader;
}
Mesh::Mesh(std::vector<Triangle*> triangles) : faces(std::move(triangles)) {}

std::vector<Triangle*> Mesh::getFaces() const
{
	return faces;
}

void Mesh::setFaces(const std::vector<Triangle*>& faces)
{
	this->faces = faces;
}

Transform Mesh::getTransform() const
{
	return transform;
}

bool Mesh::loadObjFile(std::string filename, const Vector3f& color)
{
	std::ifstream f(filename);
	if (!f.is_open())
		return false;

	//Local cache of verts
	std::vector<Vector3f> verts;

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream stream;
		stream << line;

		char junk;

		if (line[0] == 'v')
		{
			Vector3f v;
			stream >> junk >> v.x >> v.y >> v.z;
			verts.push_back(v);
		}
		else if (line[0] == 'f')
		{
			int f[3];
			stream >> junk >> f[0] >> f[1] >> f[2];

			Triangle t(verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1], color);

			faces.push_back(&t);
		}
	}

	return true;
}
