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

	void print(Camera& camera) const noexcept;

protected:
	Vector3f computeScreenCoordinates(const Vector3f& vertex) const;
	Vector3f getBarycentricCoords(const Vector3f& vertex0, const Vector3f& vertex1, const Vector3f& vertex2,
		const unsigned int& pixelX, const unsigned int& pixelY) const;

	unsigned int imageWidth;
	unsigned int imageHeight;
	Scene* scene;
	std::shared_ptr<Image> image;

private:
	float edgeFunction(const Vector3f& a, const Vector3f& b, const Vector2<unsigned int>& c) const;
	float edgeFunction(const Vector3f& a, const Vector3f& b, const Vector3f& c) const;

	float** depthBuffer;
};
