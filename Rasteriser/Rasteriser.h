#pragma once
#include <memory>
#include "Scene.h"
#include "Image.h"
#include "Vector2.h"
#include "Camera.h"

class Rasteriser
{
public:
	Rasteriser(Scene& scene, std::shared_ptr<Image>& image);
	~Rasteriser();

	void print(const Camera& camera) const;

protected:
	Vector3f computeScreenCoordinates(const Vector3f& vertex) const;
	Vector3f getBarycentricCoords(const Vector3f& vertex0, const Vector3f& vertex1, const Vector3f& vertex2,
	                              const unsigned int& pixelX, const unsigned int& pixelY) const;

	Scene* scene;
	std::shared_ptr<Image> image;
	unsigned int imageWidth;
	unsigned int imageHeight;

private:
	float edgeFunction(const Vector3f& a, const Vector3f& b, const Vector2<unsigned int>& c) const;
	float edgeFunction(const Vector3f& a, const Vector3f& b, const Vector3f& c) const;

	float dx12;
	float dx23;
	float dx31;
	float dy12;
	float dy23;
	float dy31;

	float** depthBuffer;
};
