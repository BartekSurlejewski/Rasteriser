#pragma once
#include <string>
#include "Vector3.h"

class Image {
private:
	unsigned int width, height;
public:
	Image(unsigned int width, unsigned int height);
	Image(std::string filepath);

	virtual unsigned int getWidth() const;
	virtual unsigned int getHeight() const;
	virtual void saveToFile(const std::string &filename) = 0;
	virtual Vector3f readPixel(unsigned int x, unsigned int y) const = 0;
	virtual void writePixel(unsigned int x, unsigned int y, const Vector3f& color) = 0;
	virtual void writePixel(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue) = 0;
	virtual void writeAll(const Vector3f& color) = 0;
	virtual void writeAll(unsigned char red, unsigned char green, unsigned char blue) = 0;
};


