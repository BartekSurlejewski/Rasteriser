#include "pch.h"
#include <iostream>
#include "Rasteriser.h"
#include "BitmapImage.h"
#include <ctime>
#include <chrono>
#include <memory>
#include "Settings.h"

const std::string currentDateTime();

int main()
{
	const std::string filename = currentDateTime() + ".bmp";

	Vector3f v1 = Vector3f(-0.75, -0.75, 0);
	Vector3f v2 = Vector3f(-0.75, 0.75, 0);
	Vector3f v3 = Vector3f(0.75, -0.75, 0);

	Vector3f v4 = Vector3f(-0.8, 0.6, -1);
	Vector3f v5 = Vector3f(-0.8, -0.6, -1);
	Vector3f v6 = Vector3f(0.75, 0.1, 10);

	Vertex vert1(v1, Vector3f(1, 0, 0));
	Vertex vert2(v2, Vector3f(1, 0, 0));
	Vertex vert3(v3, Vector3f(1, 0, 0));

	Vertex vert4(v4, Vector3f(0, 1, 0));
	Vertex vert5(v5, Vector3f(1, 1, 1));
	Vertex vert6(v6, Vector3f(0, 0, 1));

	Triangle t1(vert1, vert3, vert2);
	Triangle t2(vert4, vert5, vert6);

	std::vector<Triangle*> tris;
	tris.push_back(&t1);
	tris.push_back(&t2);
	Model p1(tris);

	Scene scene;
	scene.addPrimitive(p1);

	std::shared_ptr<Image> image(new BitmapImage(Settings::ImageWidth, Settings::ImageHeight));
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
