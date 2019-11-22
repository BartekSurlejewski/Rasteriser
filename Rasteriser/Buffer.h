#pragma once
class Buffer
{
public:
	Buffer() = default;
	virtual void setSize();
	void clearColor();
	void clearDepth();

protected:
	unsigned int color;
	unsigned short depth, width, height, length, minx, maxx, miny, maxy;
};

