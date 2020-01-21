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
	for (int i = 0; i < 16; i++)
	{
		M[i] = 0;
	}
	
	for (int i = 0; i < 4; i++)
	{
		M[i * 4 + i] = diag;
	}
}

Matrix4x4f::Matrix4x4f(const Vector4f& v1, const Vector4f& v2, const Vector4f& v3, const Vector4f& o) : Matrix4x4f(
	v1.x, v1.y, v1.z, v1.w,
	v2.x, v2.y, v2.z, v2.w,
	v3.x, v3.y, v3.z, v3.w,
	o.x, o.y, o.z, o.w) {}

Matrix4x4f& Matrix4x4f::operator=(Matrix4x4f other)
{
	for (int i = 0; i < size; i++)
	{
		M[i] = other[i];
	}

	return *this;
}

float& Matrix4x4f::operator[](int index)
{
	if (index < size && index >= 0)
	{
		return this->M[index];
	}
}

Matrix4x4f& Matrix4x4f::operator*=(Matrix4x4f& other)
{
	*this = *this * other;
	return *this;
}

Matrix4x4f& Matrix4x4f::operator*=(float scalar)
{
	for (int i = 0; i < size; ++i)
		this->M[i] = M[i] * scalar;
	return *this;
}

Matrix4x4f& Matrix4x4f::Transpose()
{
	//Matrix4x4f N = M;
	for (int i = 0; i < Matrix4x4f::N; ++i)
		for (int j = i + 1; j < Matrix4x4f::N; ++j)
		{
			std::swap(this[size * i + j], this[size * j + i]);
		}
	return *this;
}

const Matrix4x4f Matrix4x4f::Identity()
{
	Matrix4x4f m(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
	
	return m;
}
