#pragma once
#include "Vector4.h"

class Matrix4x4f
{
public:
	Matrix4x4f(float m0, float m1, float m2, float m3,
	           float m4, float m5, float m6, float m7,
	           float m8, float m9, float m10, float m11,
	           float m12, float m13, float m14, float m15);
	Matrix4x4f(float diag = 1.0f);
	Matrix4x4f(const Vector4f& v1, const Vector4f& v2, const Vector4f& v3, const Vector4f& o);
	//Matrix4x4f();
	Matrix4x4f& operator=(Matrix4x4f other);

	float& operator[](int index);
	Matrix4x4f& operator*=(Matrix4x4f& other);
	Matrix4x4f& operator*=(float scalar);
	Matrix4x4f& Transpose();
	const static Matrix4x4f Identity();
	
	static const int N = 4;
private:
	static const int size = N * N;
	//row based storage
	//column based basis vectors
	float M[size];
};

inline Vector4f operator*(Matrix4x4f& left, const Vector4f& right)
{
	float x = left[0] * right.x + left[1] * right.y + left[2] * right.z + left[3] * right.w;
	float y = left[4] * right.x + left[5] * right.y + left[6] * right.z + left[7] * right.w;
	float z = left[8] * right.x + left[9] * right.y + left[10] * right.z + left[11] * right.w;
	float w = left[12] * right.x + left[13] * right.y + left[14] * right.z + left[15] * right.w;
	
	return Vector4f(x, y, z, w);
}

inline Vector3f operator*(Matrix4x4f& left, const Vector3f& right)
{
	Vector4f tmp = left *  Vector4f(right, 1);

	return Vector3f(tmp.x, tmp.y, tmp.z);
}

inline Matrix4x4f operator*(Matrix4x4f& left, Matrix4x4f& right)
{
	Matrix4x4f m;
	int N = Matrix4x4f::N;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			float sum = 0.0f;
			for (int k = 0; k < N; ++k)
				sum += left[N * i + k] * right[N * k + j];
			m[N * i + j] = sum;
		}
	
	return m;
}