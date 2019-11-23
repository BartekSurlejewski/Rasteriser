#include "pch.h"
#include <iostream>
#include "Rasteriser.h"
#include "bitmap_image.hpp"
#include "BitmapImage.h"
#include <ctime>
#include <chrono>
#include <memory>

const std::string currentDateTime();

int main()
{
	const unsigned int height = 500,
		width = 500;
	const std::string filename = currentDateTime() + ".bmp";

	Vector3f v1 = Vector3f(-1, -1, 0);
	Vector3f v2 = Vector3f(0, 1, 0);
	Vector3f v3 = Vector3f(1, -1, 0);
	Vector3f color = Vector3f(1, 0, 0);

	Triangle t1(v1, v2, v3, color);

	std::vector<std::shared_ptr<Triangle>> tris;
	tris.push_back(std::make_shared<Triangle>(t1));
	Primitive p1(tris);

	Scene scene;
	scene.addPrimitive(p1);

	std::shared_ptr<Image> image(new BitmapImage(width, height));
	const Vector3f bgColor(0.0, 0.0, 0.0);
	image->writeAll(bgColor);

	Rasteriser rasteriser(scene, image);
	rasteriser.print();

	image->saveToFile("images/" + filename);
}

const std::string currentDateTime()
{
	time_t     now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm  timeStruct;
	char       buf[80];
	localtime_s(&timeStruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d--%H-%M-%S", &timeStruct);
	return buf;
}
