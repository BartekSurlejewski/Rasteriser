#include "pch.h"
#include "Transform.h"

Transform::Transform() : worldMatrix(Matrix4x4f::Identity())
{}
Matrix4x4f Transform::getWorldMatrix() const { return worldMatrix; }
void Transform::setWorldMatrix(const Matrix4x4f& worldMatrix) { this->worldMatrix = worldMatrix; }

void Transform::translate(const Vector3f& translation)
{
	Matrix4x4f m(Matrix4x4f(1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1));

	worldMatrix = m * worldMatrix;
}

void Transform::scale(const Vector3f& v)
{
	Matrix4x4f m(Matrix4x4f(v.x, 0, 0, 0,
		0, v.y, 0, 0,
		0, 0, v.z, 0,
		0, 0, 0, 1));

	worldMatrix = m * worldMatrix;
}

void Transform::rotate(const float& angle, const Vector3f& rotationVector)
{
	float s(sinf(angle * M_PI / 180));
	float c(cosf(angle * M_PI / 180));

	Vector3f normalizedRotationVector(rotationVector.normalized());

	Matrix4x4f m(Matrix4x4f(normalizedRotationVector.x * normalizedRotationVector.x * (1 - c) + c, normalizedRotationVector.x * normalizedRotationVector.y * (1 - c) - normalizedRotationVector.z * s,
		normalizedRotationVector.x * normalizedRotationVector.z * (1 - c) + normalizedRotationVector.y * s, 0,
		normalizedRotationVector.y * normalizedRotationVector.x * (1 - c) + normalizedRotationVector.z * s, normalizedRotationVector.y * normalizedRotationVector.y * (1 - c) + c,
		normalizedRotationVector.y * normalizedRotationVector.z * (1 - c) - normalizedRotationVector.x * s, 0,
		normalizedRotationVector.x * normalizedRotationVector.z * (1 - c) - normalizedRotationVector.y * s, normalizedRotationVector.y * normalizedRotationVector.z * (1 - c) + normalizedRotationVector.x * s,
		normalizedRotationVector.z * normalizedRotationVector.z * (1 - c) + c, 0,
		0, 0, 0, 1));

	worldMatrix = m * worldMatrix;
}