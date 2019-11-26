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

	Vector3f v1 = Vector3f(-0.5, -1, 0);
	Vector3f v2 = Vector3f(0, 1, 0);
	Vector3f v3 = Vector3f(0.5, -1, 0);
	Vector3f color = Vector3f(1, 0, 0);

	Triangle t1(v1, v2, v3, color);

	std::vector<Triangle> tris;
	tris.push_back(t1);
	Primitive p1(tris);

	Scene scene;
	scene.addPrimitive(p1);

	std::shared_ptr<Image> image(new BitmapImage(width, height));
	const Vector3f bgColor(0.0, 0.0, 0.0);
	image->writeAll(bgColor);
	Rasteriser rasteriser(scene, image);

	std::cout << "Rendering scene with: " << scene.getPrimitives().size() << (scene.getPrimitives().size() == 1 ? " object\n" : " objects\n");
	auto startTime = std::chrono::system_clock::now();
	rasteriser.print();
	auto endTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsedSeconds = endTime - startTime;
	std::cout << "Rendering took: " << elapsedSeconds.count() << "s\n";
	std::cout << "FPS: " << 1 / elapsedSeconds.count() << "s\n";
	image->saveToFile("images/" + filename);

	std::cout << "Saved image as: " << filename << std::endl;
	return 0;
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
