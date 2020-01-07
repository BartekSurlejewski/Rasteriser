#pragma once
#include "MeshLoader.h"

class OBJLoader : public MeshLoader {
public:
	void loadMesh(const std::string &filePath, Mesh& targetMesh, bool loadNormals,
		const Vector3f &positionOffset = Vector3f(), const Vector3f& color = Vector3f(1, 0, 0)) override;

private:
	std::vector<Vector3f> vertices;
	std::vector<Vector3f> normals;
	std::vector<Triangle*> faces;

	void parseVertex(std::vector<std::string> vertexLine, Vector3f positionOffset);
	void parseNormal(std::vector<std::string> normalLine);
	void parseFace(std::vector<std::string> faceLine, bool loadNormals, Vector3f color);
	void init();
};

