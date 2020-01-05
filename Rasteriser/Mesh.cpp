#include "pch.h"
#include "Mesh.h"
#include <fstream>
#include <strstream>

Mesh::Mesh(std::vector<Triangle*> triangles) : triangles(std::move(triangles)) {}

std::vector<Triangle*> Mesh::getTriangles() const
{
	return triangles;
}

Transform* Mesh::getTransform()
{
	return &transform;
}

bool Mesh::LoadObjFile(std::string filename, const Vector3f& color)
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

		if(line[0] == 'v')
		{
			Vector3f v;
			stream >> junk >> v.x >> v.y >> v.z;
			verts.push_back(v);
		}
		else if(line[0] == 'f')
		{
			int f[3];
			stream >> junk >> f[0] >> f[1] >> f[2];

			Triangle t(verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1], color);
			
			triangles.push_back(&t);
		}
	}

	return true;
}
