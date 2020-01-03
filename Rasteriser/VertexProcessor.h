#pragma once
#include "Matrix4x4f.h"

class VertexProcessor
{
public:
	VertexProcessor();

	Matrix4x4f viewMatrix;
	Matrix4x4f projectionMatrix;

	void setPerspective(float& fovY, const float& aspect, const float& near, const float& far);
	void setLookAt(const Vector3f& eye, const Vector3f& center, Vector3f& up);
	void scale(const Vector3f& scaleVector);
	void rotate(const Vector3f& rotationVector);
	void translate(const Vector3f& translationVector);
	
};

