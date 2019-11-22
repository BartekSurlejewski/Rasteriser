#pragma once
#include <cassert>
#include <cmath>

template <class T>
struct Vector2
{
public:
	T x, y;
	
	Vector2();
	Vector2(T xy);
	Vector2(T x, T y);
	Vector2(const Vector2<T>& other);
	Vector2<T>& operator=(const Vector2<T> other);

	bool equals(const Vector2<T>& other, float epsilon = 0.001f) const;
	float dotProduct(const Vector2<T>& other) const;
	float crossProduct(const Vector2<T>& other) const;

	Vector2<T> operator-() const;
	Vector2<T> operator+() const;

	bool operator==(const Vector2<T>& other) const;
	bool operator!=(const Vector2<T>& other) const;

	Vector2<T>& operator+=(const Vector2<T>& other);
	Vector2<T>& operator-=(const Vector2<T>& other);
	Vector2<T>& operator*=(float value);
	Vector2<T>& operator/=(float value);

	float lengthSquared() const;
	float length() const;
	Vector2<T> normalized() const;
	
	Vector2<T> orthogonal() const;
};

template <class T>
Vector2<T>::Vector2() : Vector2(0, 0) {}

template <class T>
Vector2<T>::Vector2(T xy) : Vector2(xy, xy) {}

template <class T>
Vector2<T>::Vector2(T x, T y)
{
	this->x = x;
	this->y = y;
}

template <class T>
Vector2<T>::Vector2(const Vector2<T>& other) : Vector2(other.x, other.y) {}

template <class T>
Vector2<T>& Vector2<T>::operator=(const Vector2<T> other)
{
	x = other.x;
	y = other.y;
	return *this;
}

template <class T>
bool Vector2<T>::equals(const Vector2<T>& other, float epsilon) const
{
	return abs(x - other.x) < epsilon &&
		abs(y - other.y) < epsilon;
}

template <class T>
float dot(const Vector2<T>& left, const Vector2<T>& right)
{
	return left.x * right.x + left.y * right.y;
}

template <class T>
float cross(const Vector2<T>& left, const Vector2<T>& right)
{
	return left.x * right.y - left.y * right.x;
}

template <class T>
float Vector2<T>::dotProduct(const Vector2<T>& other) const
{
	return dot(*this, other);
}

template <class T>
float Vector2<T>::crossProduct(const Vector2<T>& other) const
{
	return cross(*this, other);
}

template <class T>
Vector2<T> Vector2<T>::operator-() const
{
	return Vector2<T>(-x, -y);
}

template <class T>
Vector2<T> Vector2<T>::operator+() const
{
	return *this;
}

template <class T>
bool Vector2<T>::operator==(const Vector2<T>& other) const
{
	return equals(other);
}

template <class T>
bool Vector2<T>::operator!=(const Vector2<T>& other) const
{
	return !(*this == other);
}

template <class T>
Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x + right.x, left.y + right.y);
}

template <class T>
Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
{
	return left + (-right);
}

template <class T>
Vector2<T> operator*(const Vector2<T>& v, float f)
{
	return Vector2<T>(T(v.x * f), T(v.y * f));
}

template <class T>
Vector2<T> operator/(const Vector2<T>& v, float f)
{
	assert(f != 0.0f);
	return v * (1.0f / f);
}

template <class T>
Vector2<T> operator*(float f, const Vector2<T>& v)
{
	return v * f;
}

template <class T>
Vector2<T> operator/(float f, const Vector2<T>& v)
{
	assert(f != 0.0f);
	return v / f;
}

template <class T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other)
{
	return *this += (-other);
}

template <class T>
Vector2<T>& Vector2<T>::operator*=(float value)
{
	x *= value;
	y *= value;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator/=(float value)
{
	assert(value != 0);
	return *this *= 1.0f / value;
}

template <class T>
float Vector2<T>::lengthSquared() const
{
	return dot(*this, *this);
}

template <class T>
float Vector2<T>::length() const
{
	return sqrt(lengthSquared());
}

template <class T>
Vector2<T> Vector2<T>::normalized() const
{
	return *this / length();
}

template <class T>
Vector2<T> Vector2<T>::orthogonal() const
{
	return Vector2<T>(-y, x);
}

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;