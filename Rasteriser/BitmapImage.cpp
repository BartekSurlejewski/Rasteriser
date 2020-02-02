#include "pch.h"
#include "BitmapImage.h"

BitmapImage::BitmapImage(const unsigned int width, const unsigned int height) : Image(width, height)
{
	this->data = bitmap_image(width, height);
}

BitmapImage::BitmapImage(std::string filepath) : Image(filepath)
{
	this->data = bitmap_image(filepath);
}
void BitmapImage::saveToFile(const std::string& filename)
{
	this->data.save_image(filename);
}

Vector3f BitmapImage::readPixel(unsigned int x, unsigned int y) const
{
	const rgb color = this->data.get_pixel(x, y);
	return { color.red / 255.0F, color.green / 255.0F, color.blue / 255.0F };
}

void BitmapImage::writePixel(const unsigned int& x, const unsigned int& y, const Vector3f& color)
{
	rgb resultColor(rgb(color.x * 255, color.y * 255, color.z * 255));
	this->data.set_pixel(x, y, resultColor);
}

void BitmapImage::writeAll(const Vector3f* color)
{
	int width = getWidth();
	int height = getHeight();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			const Vector3f& pixelColor = color[x * width + y];
			rgb resultColor = rgb(pixelColor.x * 255, pixelColor.y * 255, pixelColor.z * 255);
			this->data.set_pixel(x, y, resultColor);
		}
	}
}

void BitmapImage::writePixel(unsigned int x, unsigned int y, const unsigned char red, const unsigned char green,
	const unsigned char blue)
{
	this->data.set_pixel(x, y, red, green, blue);
}

void BitmapImage::writeAll(const Vector3f& color)
{
	this->data.set_all_channels(color.x * 255, color.y * 255, color.z * 255);
}

void BitmapImage::writeAll(unsigned char red, unsigned char green, unsigned char blue)
{
	this->data.set_all_channels(red, green, blue);
}

unsigned int BitmapImage::getWidth() const
{
	return data.width();
}

unsigned int BitmapImage::getHeight() const
{
	return data.height();
}
