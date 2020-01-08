#pragma once
#include <ostream>
#include <cassert>
#include "Vector3.h"

template <class T>
struct Vector4
{
	T x, y, z, w;

	Vector4();
	Vector4(T x);
	Vector4(T x, T y, T z, T w);
	Vector4(const Vector3<T>& v, T w);
	Vector4(const Vector4<T>& other);
	Vector4<T>& operator=(const Vector4<T>& other);

	Vector3<T> GetVector3() const;
	Vector4<T> DivideW() const;

	Vector4<T> operator-() const;

	bool operator==(const Vector4<T>& other) const;
	bool operator!=(const Vector4<T>& other) const;

	Vector4<T>& operator+=(const Vector4<T>& other);
	Vector4<T>& operator-=(const Vector4<T>& other);
	T operator[](int index);

	float LengthSquared() const;
	float Length() const;
	Vector4<T> Normalize() const;
};

template <class T>
Vector4<T>::Vector4()
	: Vector4(0, 0, 0, 0) {}

template <class T>
Vector4<T>::Vector4(T x)
	: Vector4(x, x, x, x) {}

template <class T>
Vector4<T>::Vector4(T x, T y, T z, T w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

template <class T>
Vector4<T>::Vector4(const Vector3<T>& v, T w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}

template <class T>
Vector4<T>::Vector4(const Vector4<T>& other)
	: Vector4(other.x, other.y, other.z, other.w) {}

template <class T>
Vector4<T>& Vector4<T>::operator=(const Vector4<T>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

template <class T>
Vector3<T> Vector4<T>::GetVector3() const
{
	return Vector3<T>(x, y, z);
}

template <class T>
Vector4<T> Vector4<T>::DivideW() const
{
	float invW = 1.0f / w;
	return Vector4<T>(x * invW, y * invW, z * invW, w);
}

template <class T>
Vector4<T> Vector4<T>::operator-() const
{
	return Vector4<T>(-x, -y, -z, -w);
}

template <class T>
bool Vector4<T>::operator==(const Vector4<T>& other) const
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

template <class T>
bool Vector4<T>::operator!=(const Vector4<T>& other) const
{
	return !(*this == other);
}

template <class T>
Vector4<T> operator+(const Vector4<T>& left, const Vector4<T>& right)
{
	return Vector4<T>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

template <class T>
Vector4<T> operator-(const Vector4<T>& left, const Vector4<T>& right)
{
	return left + (-right);
}

template <class T>
Vector4<T> operator*(const Vector4<T>& v, float f)
{
	return Vector4<T>(v.x * f, v.y * f, v.z * f, v.w * f);
}

template <class T>
Vector4<T> operator/(const Vector4<T>& v, float f)
{
	assert(f != 0.0f);
	return v * (1.0f / f);
}

template <class T>
Vector4<T> operator/=(const Vector4<T>& v, float f)
{
	return v / f;
}

template <class T>
Vector4<T> operator*(float f, const Vector4<T>& v)
{
	return v * f;
}

template <class T>
Vector4<T> operator/(float f, const Vector4<T>& v)
{
	assert(f != 0.0f);
	return v / f;
}

template <class T>
Vector4<T> operator/=(float f, const Vector4<T>& v)
{
	return v / f;
}

template <class T>
Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& other)
{
	return *this += (-other);
}

template <class T>
T Vector4<T>::operator[](int index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}
}

template <class T>
float Vector4<T>::LengthSquared() const
{
	return Dot(*this, *this);
}

template <class T>
float Vector4<T>::Length() const
{
	return std::sqrt(LengthSquared());
}

template <class T>
Vector4<T> Vector4<T>::Normalize() const
{
	return *this / Length();
}

template <class T>
float Dot(const Vector4<T>& left, const Vector4<T>& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

//Cross product only exist in (2D), 3D, 7D

template <class T>
std::ostream& operator<<(std::ostream& stream, const Vector4<T>& vector)
{
	return stream << "[x: " << vector.x << ", y: " << vector.y << ", z: " << vector.z << ", w: " << vector.w << "]";
}

typedef Vector4<int> Vector4i;
typedef Vector4<float> Vector4f;
