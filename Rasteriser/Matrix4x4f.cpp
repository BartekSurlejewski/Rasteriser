#include "pch.h"
#include "Matrix4x4f.h"

Matrix4x4f::Matrix4x4f(const float& m0, const float& m1, const float& m2, const float& m3, const float& m4, const float& m5, const float& m6, const float& m7, const float& m8,
	const float& m9, const float& m10, const float& m11, const float& m12, const float& m13, const float& m14, const float& m15)
{
	float list[] = {
		m0, m1, m2, m3,
		m4, m5, m6, m7,
		m8, m9, m10, m11,
		m12, m13, m14, m15
	};

	for (int i = 0; i < 16; ++i)
		M[i] = list[i];
}

Matrix4x4f::Matrix4x4f(const float& diag)
{
	float list[] = {
		diag, 0, 0, 0,
		0, diag, 0, 0,
		0, 0, diag, 0,
		0, 0, 0, diag
	};

	for (int i = 0; i < 16; ++i)
		M[i] = list[i];
}

Matrix4x4f::Matrix4x4f(const Vector4f& v1, const Vector4f& v2, const Vector4f& v3, const Vector4f& o) : Matrix4x4f(
	v1.x, v1.y, v1.z, v1.w,
	v2.x, v2.y, v2.z, v2.w,
	v3.x, v3.y, v3.z, v3.w,
	o.x, o.y, o.z, o.w) {}

Matrix4x4f& Matrix4x4f::operator=(Matrix4x4f other)
{
	M[0] = other[0];
	M[1] = other[1];
	M[2] = other[2];
	M[3] = other[3];
	M[4] = other[4];
	M[5] = other[5];
	M[6] = other[6];
	M[7] = other[7];
	M[8] = other[8];
	M[9] = other[9];
	M[10] = other[10];
	M[11] = other[11];
	M[12] = other[12];
	M[13] = other[13];
	M[14] = other[14];
	M[15] = other[15];

	return *this;
}

inline float& Matrix4x4f::operator[](int index)
{
	if (index < size && index >= 0)
	{
		return this->M[index];
	}
}

inline Matrix4x4f& Matrix4x4f::operator*=(Matrix4x4f& other)
{
	*this = *this * other;
	return *this;
}

inline Matrix4x4f& Matrix4x4f::operator*=(float scalar)
{
	M[0] *= scalar;
	M[1] *= scalar;
	M[2] *= scalar;
	M[3] *= scalar;
	M[4] *= scalar;
	M[5] *= scalar;
	M[6] *= scalar;
	M[7] *= scalar;
	M[8] *= scalar;
	M[9] *= scalar;
	M[10] *= scalar;
	M[11] *= scalar;
	M[12] *= scalar;
	M[13] *= scalar;
	M[14] *= scalar;
	M[15] *= scalar;

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

Matrix4x4f Matrix4x4f::Identity()
{
	Matrix4x4f m(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	return m;
}
