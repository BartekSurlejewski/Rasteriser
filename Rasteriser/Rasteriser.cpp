#include "pch.h"
#include "Rasteriser.h"
#include <iostream>

Rasteriser::Rasteriser(const Scene& scene) : scene(std::make_unique<Scene>(scene)) {}

void Rasteriser::print() const
{
	std::vector<Primitive> primitives = scene->getPrimitives();

	for (unsigned int i = 0; i < primitives.size(); i++)
	{
		// STEP I: project vertices of the triangle using perspective projection
		const Primitive& primitive = primitives[i];
		const std::vector<Triangle>& triangles = primitive.getTriangles();

		for (unsigned int j = 0; j < triangles.size(); i++)
		{
			// STEP II: is this pixel contained in the projected image of the triangle?
			
		}
	}
}
