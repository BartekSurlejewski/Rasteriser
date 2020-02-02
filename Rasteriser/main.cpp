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

	//octahedron
	Mesh octahedron("models/octahedron.obj", { 0, 0, 1 });
	Transform& cubeTransform = octahedron.getTransform();
	cubeTransform.scale({ 0.5, 0.5, 0.5 });
	cubeTransform.translate({ 1, 1.5, 0 });

	Mesh octahedron1("models/octahedron.obj", { 0, 0, 1 });
	Transform& octahedron1Transform = octahedron1.getTransform();
	octahedron1Transform.scale({ 0.5, 0.5, 0.5 });
	octahedron1Transform.translate({ 1.5, 0, 0 });

	Mesh octahedron2("models/octahedron.obj", { 0, 0, 1 });
	Transform& octahedron2Transform = octahedron2.getTransform();
	octahedron2Transform.scale({ 0.5, 0.5, 0.5 });
	octahedron2Transform.translate({ 1, -1.5, 0 });

	//monkey
	Mesh monkey("models/monkey.obj", { 0, 1, 0 });
	//Transform& monkeyTransform = monkey.getTransform();
	//monkeyTransform.scale({ 0.5 });
	//monkeyTransform.rotate(90, { 0, 1, 0 });
	//monkeyTransform.translate({ 0, 1, 0 });	

	//Mesh sphere("models/sphere.obj", { 0, 1, 0 });
	//Transform& sphereTransform = sphere.getTransform();
	//sphereTransform.scale({ 0.1, 0.1, 0.1 });
	//sphereTransform.rotate(90, {1, 1, 0});

	Mesh octahedron3("models/octahedron.obj", { 0, 0, 1 });
	Transform& octahedron3Transform = octahedron3.getTransform();
	octahedron3Transform.scale({ 0.5, 0.5, 0.5 });
	octahedron3Transform.translate({ -1, 1.5, 0 });

	Mesh octahedron4("models/octahedron.obj", { 0, 0, 1 });
	Transform& octahedron4Transform = octahedron4.getTransform();
	octahedron4Transform.scale({ 0.5, 0.5, 0.5 });
	octahedron4Transform.translate({ -1.5, 0, 0 });

	Mesh octahedron5("models/octahedron.obj", { 0, 0, 1 });
	Transform& octahedron5Transform = octahedron5.getTransform();
	octahedron5Transform.scale({ 0.5, 0.5, 0.5 });
	octahedron5Transform.translate({ -1, -1.5, 0 });


	scene.addPrimitive(monkey);
	//scene.addPrimitive(sphere);
	scene.addPrimitive(octahedron);
	scene.addPrimitive(octahedron1);
	scene.addPrimitive(octahedron2);
	scene.addPrimitive(octahedron3);
	scene.addPrimitive(octahedron4);
	scene.addPrimitive(octahedron5);

	std::shared_ptr<Image> image(new (std::nothrow) BitmapImage(Settings::ImageWidth, Settings::ImageHeight));
	const Vector3f bgColor(0.3, 0.6, 1);
	image->writeAll(bgColor);
	Rasteriser rasteriser(scene, image);

	Camera camera;
	//Camera Transformations
	camera.setLookAt({ 0, 0, 15.0f }, { 0 }, Vector3f(0.0f, 1.0f, 0.0f));
	camera.setPerspective(120, Settings::ImageWidth / Settings::ImageHeight, 0.01f, 10000);

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

const std::string currentDateTime()
{
	time_t     now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm  timeStruct;
	char       buf[80];
	localtime_s(&timeStruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d--%H-%M-%S", &timeStruct);
	return buf;
}
