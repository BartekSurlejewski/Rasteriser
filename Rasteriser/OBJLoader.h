#pragma once
#include "MeshLoader.h"

class OBJLoader : public MeshLoader {
public:
	void loadMesh(const std::string& filePath, Mesh& targetMesh, bool loadNormals,
		const Vector3f& color = Vector3f(1, 0, 0), const Vector3f &positionOffset = Vector3f()) override;

private:
	std::vector<Vector3f> vertices;
	std::vector<Vector3f> normals;
	std::vector<Triangle> faces;

	void parseVertex(const std::vector<std::string>& vertexLine, const Vector3f& positionOffset);
	void parseNormal(const std::vector<std::string>& normalLine);
	void parseFace(const std::vector<std::string>& faceLine, bool loadNormals, const Vector3f& color);
	void init();
};

