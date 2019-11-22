#pragma once
#include "bitmap_image.hpp"
#include "Image.h"

class BitmapImage : public Image
{
public:
	BitmapImage(unsigned int width, unsigned int height);
	explicit BitmapImage(std::string filepath);

	void saveToFile(const std::string &filename) override;
	Vector3f readPixel(unsigned int x, unsigned int y) const override;
	void writePixel(unsigned int x, unsigned int y, const Vector3f& color) override;
	void writePixel(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue) override;
	void writeAll(const Vector3f& color) override;
	void writeAll(unsigned char red, unsigned char green, unsigned char blue) override;

	unsigned int getWidth() const override;
	unsigned int getHeight() const override;

private:
	bitmap_image data;
};

