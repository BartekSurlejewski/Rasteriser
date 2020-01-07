#pragma once
#include "Matrix4x4f.h"

class Camera
{
public:
	Camera();

	Matrix4x4f getViewMatrix() const;
	Matrix4x4f getProjectionMatrix() const;
	
	void setPerspective(float fovY2, const float& aspect, const float& near, const float& far);
	void setLookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);
	void scale(const Vector3f& scaleVector);
	void rotate(const Vector3f& rotationVector);
	void translate(const Vector3f& translationVector);


private:
	Matrix4x4f viewMatrix;
	Matrix4x4f projectionMatrix;
};

