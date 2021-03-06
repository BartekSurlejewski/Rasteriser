#define _USE_MATH_DEFINES
#pragma once
#include "Vector3.h"
#include "Matrix4x4f.h"

class Transform
{
public:
	Transform();

	Matrix4x4f getWorldMatrix() const;
	void setWorldMatrix(const Matrix4x4f& worldMatrix);

	void translate(const Vector3f& translation);
	void scale(const Vector3f& v);
	void rotate(const float& angle, const Vector3f& rotationVector);

private:
	Matrix4x4f worldMatrix;
};
