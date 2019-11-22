#include "pch.h"
#include <iostream>
#include "Rasteriser.h"
#include "bitmap_image.hpp"
#include "BitmapImage.h"
#include <ctime>
#include <chrono>

const std::string currentDateTime();

int main()
{
	const unsigned int height = 500,
		width = 500;
	const std::string filename = currentDateTime() + ".bmp";

	BitmapImage image(width, height);
	const Vector3f color(1.0, 0.0, 0.0);
	image.writeAll(color);
	image.saveToFile(filename);
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
