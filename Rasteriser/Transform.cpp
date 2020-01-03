#include "pch.h"
#include "Transform.h"
#include <math.h>

Transform::Transform() {}
Matrix4x4f Transform::getWorldMatrix() const { return worldMatrix; }
void Transform::setWorldMatrix(const Matrix4x4f& worldMatrix) { this->worldMatrix = worldMatrix; }

void Transform::translate(const Vector3f& translation)
{
	//position += translation;

	Matrix4x4f m = Matrix4x4f(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translation.x, translation.y, translation.z, 1);

	worldMatrix = m * worldMatrix;
}

void Transform::scale(const Vector3f& v)
{
	//scale *= v;

	Matrix4x4f m = Matrix4x4f(v.x, 0, 0, 0,
		0, v.y, 0, 0,
		0, 0, v.z, 0,
		0, 0, 0, 1);

	worldMatrix = m * worldMatrix;
}

void Transform::rotate(const float& angle, Vector3f& rotationVector)
{
	float s = sinf(angle * M_PI / 180);
	float c = cosf(angle * M_PI / 180);

	rotationVector = rotationVector.normalized();

	Matrix4x4f m = Matrix4x4f(rotationVector.x * rotationVector.x * (1 - c) + c, rotationVector.y * rotationVector.x * (1 - c) + rotationVector.z * s, rotationVector.x * rotationVector.z * (1 - c) - rotationVector.y * s, 0,
		rotationVector.x * rotationVector.y * (1 - c) - rotationVector.z * s, rotationVector.y * rotationVector.y * (1 - c) + c, rotationVector.y * rotationVector.z * (1 - c) + rotationVector.x * s, 0,
		rotationVector.x * rotationVector.z * (1 - c) + rotationVector.y * s, rotationVector.y * rotationVector.z * (1 - c) - rotationVector.x * s, rotationVector.z * rotationVector.z * (1 - c) + c, 0,
		0, 0, 0, 1);

	worldMatrix = m * worldMatrix;
}