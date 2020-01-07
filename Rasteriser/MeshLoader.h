#pragma once
#include "Mesh.h"

class MeshLoader {
public:
	virtual void loadMesh(const std::string &filePath, Mesh& targetMesh, bool loadNormals,
		const Vector3f &positionOffset = Vector3f(), const Vector3f& color = Vector3f(1, 0, 0)) = 0;
};

