#pragma once
#include <memory>
#include "Scene.h"
#include "Image.h"

class Rasteriser
{
public:
	Rasteriser(const Scene& scene, std::shared_ptr<Image>& image);

	void print() const;

protected:
	Vector3f orthogonalProject(const Vector3f& vertex) const;
	bool pixelContainedIn2DTriangle(const Vector3f& vertex0, const Vector3f& vertex1, const Vector3f& vertex2, unsigned pixelX, unsigned pixelY) const;

	std::shared_ptr<Scene> scene;
	std::shared_ptr<Image> image;
};

