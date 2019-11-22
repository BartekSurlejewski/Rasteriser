#pragma once
#include <memory>
#include "Buffer.h"
#include "Scene.h"

class Rasteriser
{
public:
	Rasteriser(const Scene& scene);
	Rasteriser() = default;

	void print() const;

protected:
	std::unique_ptr<Scene> scene;
};

