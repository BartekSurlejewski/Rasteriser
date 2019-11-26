#include "pch.h"
#include "Matrix4x4f.h"

Matrix4x4f::Matrix4x4f(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8,
                       float m9, float m10, float m11, float m12, float m13, float m14, float m15)
{
	float list[] = {
		m0, m1, m2, m3,
		m4, m5, m6, m7,
		m8, m9, m10, m11,
		m12, m13, m14, m15
	};
	int i = 0;
	for (float& f : list)
		M[i++] = f;
}

Matrix4x4f::Matrix4x4f(float diag)
{
	for (int i = 0; i < size; i++)
	{
		if (i % N == i < N)
		{
			M[i] = diag;
		}
		else
		{
			M[i] = 0.0f;
		}
	}
}

Matrix4x4f::Matrix4x4f(const Vector4f& v1, const Vector4f& v2, const Vector4f& v3, const Vector4f& o) : Matrix4x4f(
	v1.x, v1.y, v1.z, v1.w,
	v2.x, v2.y, v2.z, v2.w,
	v3.x, v3.y, v3.z, v3.w,
	o.x, o.y, o.z, o.w) {}

float& Matrix4x4f::operator[](int index)
{
	if (index < size && index > 0)
	{
		return M[index];
	}
}

Vector4f Matrix4x4f::operator*(const Vector4f& v) const
{
	float x = M[0] * v.x + M[1] * v.y + M[2] * v.z + M[3] * v.w;
	float y = M[4] * v.x + M[5] * v.y + M[6] * v.z + M[7] * v.w;
	float z = M[8] * v.x + M[9] * v.y + M[10] * v.z + M[11] * v.w;
	float w = M[12] * v.x + M[13] * v.y + M[14] * v.z + M[15] * v.w;
	return Vector4f(x, y, z, w);
}

Matrix4x4f Matrix4x4f::operator*(Matrix4x4f& other)
{
	Matrix4x4f m;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			float sum = 0.0f;
			for (int k = 0; k < N; ++k)
				sum += M[size * i + k] * (other)[size * k + j];
			m[size * i + j] = sum;
		}
	return m;
}

Matrix4x4f Matrix4x4f::operator*(float scalar) const
{
	Matrix4x4f N;
	for (int i = 0; i < size; ++i)
		N.M[i] = M[i] * scalar;
	return N;
}

Matrix4x4f Matrix4x4f::Transpose(const Matrix4x4f& M)
{
	Matrix4x4f N = M;
	for (int i = 0; i < Matrix4x4f::N - 1; ++i)
		for (int j = i + 1; j < Matrix4x4f::N; ++j)
		{
			std::swap(N[size * i + j], N[size * j + i]);
		}
	return N;
}
