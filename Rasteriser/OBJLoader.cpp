#include "pch.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "OBJLoader.h"
#include "StringUtils.h"

void OBJLoader::loadMesh(const std::string &filePath, Mesh& targetMesh, bool loadNormals,
	const Vector3f& color, const Vector3f &positionOffset) {
	init();
	std::cout << "Parsing file: " << filePath << std::endl;

	std::ifstream inputFile(filePath);
	if (!inputFile || !inputFile.good()) {
		std::cerr << "Failed to open file: " << filePath << std::endl;
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		std::vector<std::string> splitLine = StringUtils::split(line, ' ', true);
		if (!splitLine.empty() && !splitLine.front().empty()) {
			if (splitLine.front() == "v") {
				std::vector<std::string> vertexLine(splitLine.begin() + 1, splitLine.end());
				parseVertex(vertexLine, positionOffset);
			}
			else if (splitLine.front() == "vn") {
				std::vector<std::string> normalLine(splitLine.begin() + 1, splitLine.end());
				parseNormal(normalLine);
			}
			else if (splitLine.front() == "f") {
				std::vector<std::string> faceLine(splitLine.begin() + 1, splitLine.end());
				parseFace(faceLine, loadNormals, color);
			}
		}
	}

	std::cout << " - Number of vertices acquired: " << vertices.size() << std::endl
		<< " - Number of normals acquired: " << normals.size() << std::endl
		<< " - Number of faces acquired: " << faces.size() << std::endl;

	targetMesh.setFaces(this->faces);
}

void OBJLoader::parseVertex(const std::vector<std::string>& vertexLine, const Vector3f& positionOffset) {
	Vector3f vertex = Vector3f(std::stod(vertexLine[0]) + positionOffset.x, std::stod(vertexLine[1]) + positionOffset.y, std::stod(vertexLine[2]) + positionOffset.z);
	this->vertices.push_back(vertex);
}

void OBJLoader::parseNormal(const std::vector<std::string>& normalLine) {
	Vector3f normal = Vector3f(std::stod(normalLine[0]), std::stod(normalLine[1]), std::stod(normalLine[2])).normalized();
	this->normals.push_back(normal);
}

void OBJLoader::parseFace(const std::vector<std::string>& faceLine, bool loadNormals, const Vector3f& color) {
	std::vector<int> faceVertexIndices;
	std::vector<int> faceTextureIndices;
	std::vector<int> faceNormalIndices;

	for (const auto &vertexInfo : faceLine) {
		std::vector<std::string> splitVertexInfo = StringUtils::split(vertexInfo, '/', false);

		faceVertexIndices.push_back(std::stoi(splitVertexInfo[0]));

		if (splitVertexInfo.size() == 2) {
			if (!splitVertexInfo[1].empty()) {
				faceTextureIndices.push_back(std::stoi(splitVertexInfo[1]));
			}
		}
		else if (splitVertexInfo.size() == 3) {
			if (!splitVertexInfo[1].empty()) {
				faceTextureIndices.push_back(std::stoi(splitVertexInfo[1]));
			}
			if (!splitVertexInfo[2].empty()) {
				faceNormalIndices.push_back(std::stoi(splitVertexInfo[2]));
			}
		}
	}

	Triangle face;
	if (faceNormalIndices.empty() || !loadNormals)
	{
		Vertex v0(vertices[(faceVertexIndices[0] - 1)], color);
		Vertex v1(vertices[(faceVertexIndices[1] - 1)], color);
		Vertex v2(vertices[(faceVertexIndices[2] - 1)], color);

		face = Triangle(v0, v1, v2, false);
	}
	else 
	{
		Vector3f faceNormal;
		for (const auto &vertexNormalIndex : faceNormalIndices) {
			faceNormal += normals[vertexNormalIndex - 1];
		}
		faceNormal /= faceNormalIndices.size();

		Vertex v0(vertices[(faceVertexIndices[0] - 1)], color, faceNormal);
		Vertex v1(vertices[(faceVertexIndices[1] - 1)], color, faceNormal);
		Vertex v2(vertices[(faceVertexIndices[2] - 1)], color, faceNormal);
		
		face = Triangle(v0, v1, v2, true);
	}

	this->faces.push_back(face);
}

void OBJLoader::init() {
	this->vertices.clear();
	this->normals.clear();
	this->faces.clear();
}