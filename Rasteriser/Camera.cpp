#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	setLookAt({ 0, 0, 15.0f }, { 0.0f }, Vector3f( 0.0f, 1.0f, 0.0f ));
	setPerspective(90.0f, 1.0f, 0.01f, 50.0f);
}

Matrix4x4f& Camera::getViewMatrix()
{
	return viewMatrix;
}

Matrix4x4f& Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::setPerspective(float fovY, const float& aspect, const float& near, const float& far)
{
	fovY *= 0.0087263f;
	float f = cos(fovY) / sin(fovY);  
	//Matrix4x4f matrix = Matrix4x4f(f / aspect, 0, 0, 0,
	//								0, f, 0, 0,
	//								0, 0, (far + near) / (near - far), 1,
	//								0, 0, 2 * far * near / (near - far), 0);

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
	Vector3f s = f.crossProduct(normalizedUp);
	Vector3f u = s.crossProduct(f);

	/*Matrix4x4f matrix = Matrix4x4f(s.x, u.x, -f.x, 0,
		s.y, u.y, -f.y, 0,
		s.z, u.z, -f.z, 0,
		-eye.x, -eye.y, -eye.z, 1);*/

	Matrix4x4f matrix = Matrix4x4f(s.x, s.y, s.z, -eye.x,
		u.x, u.y, u.z, -eye.y,
		-f.x, -f.y, -f.z, -eye.z,
		0, 0, 0, 1);

	viewMatrix = matrix;
}
