#include "pch.h"
#include "Transform.h"

Transform::Transform()
{
	Matrix4x4f mat(1);
	worldMatrix = mat;
	
	Vector3f rotationVector = Vector3f(0, 0, 0);
	Vector3f translationVector = Vector3f(0, 0, 0);

	scale({ 1, 1, 1 });
	rotate(0, rotationVector);
	translate(translationVector);
}
Matrix4x4f& Transform::getWorldMatrix() { return worldMatrix; }
void Transform::setWorldMatrix(Matrix4x4f& worldMatrix) { this->worldMatrix = worldMatrix; }

void Transform::translate(const Vector3f& translation)
{
	/*Matrix4x4f m = Matrix4x4f(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translation.x, translation.y, translation.z, 1);*/

	Matrix4x4f m = Matrix4x4f(1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1);

	worldMatrix = worldMatrix * m;
}

void Transform::scale(const Vector3f& v)
{
	Matrix4x4f m = Matrix4x4f(v.x, 0, 0, 0,
		0, v.y, 0, 0,
		0, 0, v.z, 0,
		0, 0, 0, 1);

	/*Matrix4x4f m = Matrix4x4f(v.x, 0, 0, 0,
								0, v.y, 0, 0,
								0, 0, v.z, 0,
								0, 0, 0, 1);*/

	worldMatrix = worldMatrix * m;
}

void Transform::rotate(const float& angle, Vector3f& rotationVector)
{
	float s = sinf(angle * M_PI / 180);
	float c = cosf(angle * M_PI / 180);

	rotationVector = rotationVector.normalized();

	/*Matrix4x4f m = Matrix4x4f(rotationVector.x * rotationVector.x * (1 - c) + c, rotationVector.y * rotationVector.x * (1 - c) + rotationVector.z * s, rotationVector.x * rotationVector.z * (1 - c) - rotationVector.y * s, 0,
		rotationVector.x * rotationVector.y * (1 - c) - rotationVector.z * s, rotationVector.y * rotationVector.y * (1 - c) + c, rotationVector.y * rotationVector.z * (1 - c) + rotationVector.x * s, 0,
		rotationVector.x * rotationVector.z * (1 - c) + rotationVector.y * s, rotationVector.y * rotationVector.z * (1 - c) - rotationVector.x * s, rotationVector.z * rotationVector.z * (1 - c) + c, 0,
		0, 0, 0, 1);*/

	Matrix4x4f m = Matrix4x4f(rotationVector.x * rotationVector.x * (1 - c) + c, rotationVector.x * rotationVector.y * (1 - c) - rotationVector.z * s, rotationVector.x * rotationVector.z * (1 - c) + rotationVector.y * s, 0,
		rotationVector.y * rotationVector.x * (1 - c) + rotationVector.z * s, rotationVector.y * rotationVector.y * (1 - c) + c, rotationVector.y * rotationVector.z * (1 - c) - rotationVector.x * s, 0,
		rotationVector.x * rotationVector.z * (1 - c) - rotationVector.y * s,  rotationVector.y * rotationVector.z * (1 - c) + rotationVector.x * s, rotationVector.z * rotationVector.z * (1 - c) + c, 0,
		0, 0, 0, 1);

	worldMatrix = worldMatrix * m;
}