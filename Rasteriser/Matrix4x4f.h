#pragma once
#include "Vector4.h"
#include "Vector2.h"

class Matrix4x4f
{
public:
	Matrix4x4f(float m0, float m1, float m2, float m3,
		float m4, float m5, float m6, float m7,
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15);
	Matrix4x4f(float diag = 1.0f);
	Matrix4x4f(const Vector4f& v1, const Vector4f& v2, const Vector4f& v3, const Vector4f& o);
	Matrix4x4f& operator=(const Matrix4x4f& other);

	float& operator[] (int index);
	Vector4f operator*(const Vector4f& v) const;
	Matrix4x4f operator*(Matrix4x4f& other);	
	Matrix4x4f operator*(float scalar) const;

	static Matrix4x4f Identity();
	static Matrix4x4f Translate(float dx, float dy, float dz);
	static Matrix4x4f Translate(const Vector3f& dv);
	static Matrix4x4f Rotate(const Vector3f& axis, float angleDegrees);
	static Matrix4x4f Scale(float dx, float dy, float dz);
	static Matrix4x4f Scale(const Vector3f& dv);
	static Matrix4x4f Orthographic(float left, float right, float bottom, float top,
		float nearZ, float farZ);
	static Matrix4x4f Orthographic(const Vector2f& x, const Vector2f& y, const Vector2f& z);
	static Matrix4x4f Perspective(float left, float right, float bottom, float top,
		float nearZ, float farZ);
	static Matrix4x4f Perspective(const Vector2f& x, const Vector2f& y, const Vector2f& z);
	static Matrix4x4f Perspective(float fov, float aspectRatio, float near, float far);
	static Matrix4x4f View(const Vector3f& eye, const Vector3f& center, const Vector3f& up);
	static Matrix4x4f Viewport(int width, int height);

	static Matrix4x4f Transpose(const Matrix4x4f& M);

	static const int N = 4;
private:
	static const int size = N * N;
	//row based storage
	//column based basis vectors
	float M[size];
};

