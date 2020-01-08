#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	viewMatrix = Matrix4x4f::Identity();
	projectionMatrix = Matrix4x4f::Identity();
}

Matrix4x4f Camera::getViewMatrix() const
{
	return viewMatrix;
}

Matrix4x4f Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

void Camera::setPerspective(float fovY, const float& aspect, const float& near, const float& far)
{
	fovY *= 0.0087263f;
	float f = cos(fovY) / sin(fovY);  

	Matrix4x4f matrix = Matrix4x4f(f / aspect, 0, 0, 0,
									0, f, 0, 0,
									0, 0, (far + near) / (near - far), 2 * far * near / (near - far),
									0, 0, -1, 0);

	projectionMatrix = matrix;
}

void Camera::setLookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up)
{
	Vector3f f = center + -eye;
	f = f.normalized();
	const Vector3f normalizedUp = up.normalized();
	Vector3f side = f.crossProduct(normalizedUp);
	Vector3f upward = side.crossProduct(f);

	Matrix4x4f matrix = Matrix4x4f(side.x, side.y, side.z, -eye.x,
		upward.x, upward.y, upward.z, -eye.y,
		-f.x, -f.y, -f.z, -eye.z,
		0, 0, 0, 1);

	viewMatrix = matrix;
}
