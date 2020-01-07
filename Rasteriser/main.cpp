#include "pch.h"
#include <iostream>
#include "Rasteriser.h"
#include "BitmapImage.h"
#include <ctime>
#include <chrono>
#include <memory>
#include "Settings.h"

const std::string currentDateTime();
Scene setupScene();

int main()
{
	const std::string filename = currentDateTime() + ".bmp";

	Scene scene;
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
	Mesh m1(tris);

	Mesh m2("models/cube.obj", Vector3f(1, 0, 0));

	scene.addPrimitive(m2);
	
	std::shared_ptr<Image> image(new BitmapImage(Settings::ImageWidth, Settings::ImageHeight));
	const Vector3f bgColor(0.0, 0.0, 0.0);
	image->writeAll(bgColor);
	Rasteriser rasteriser(scene, image);
	
	Camera camera;
	camera.setLookAt({ 0, 0, 0.0f }, { 0.0f }, Vector3f(0.0f, -1.0f, 0.0f));
	camera.setPerspective(90.0f, 1.0f, 0.01f, 50.0f);
	
	std::cout << "Rendering scene with: " << scene.getPrimitives().size() << (scene.getPrimitives().size() == 1 ? " object\n" : " objects\n");
	auto startTime = std::chrono::system_clock::now();
	rasteriser.print(camera);
	auto endTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsedSeconds = endTime - startTime;
	std::cout << "Rendering took: " << elapsedSeconds.count() << "s\n";
	std::cout << "FPS: " << 1 / elapsedSeconds.count() << "s\n";
	image->saveToFile("images/" + filename);

	std::cout << "Saved image as: " << filename << std::endl;
	return 0;
}

Scene setupScene()
{
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
	Mesh m1(tris);

	//Mesh m2("models/cube.obj", Vector3f(1, 0, 0));

	Scene scene;
	scene.addPrimitive(m1);
	return scene;
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
