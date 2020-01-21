#pragma once
#include <ostream>

template <class T>
struct Vector3
{
public:
	T x, y, z;

	/// Creates vector between two points
	Vector3(const Vector3& p1, const Vector3& p2);
	Vector3(T x, T y, T z);
	Vector3(T xyz);
	Vector3();
	Vector3(const Vector3<T>& other);
	Vector3<T>& operator=(const Vector3<T>& other);

	Vector3<T> normalized() const;
	float getMagnitude() const;
	float dotProduct(const Vector3& other) const;
	Vector3<T> crossProduct(const Vector3& other) const;

	Vector3<T> operator+() const;
	Vector3<T> operator-() const;
	Vector3<T>& operator+=(const Vector3& other);
	Vector3<T>& operator-=(const Vector3& other);
	Vector3<T>& operator*=(const Vector3& other);
	Vector3<T>& operator/=(const Vector3& other);

	const static Vector3<T> Zero();
};

template <class T>
Vector3<T>::Vector3(const Vector3& p1, const Vector3& p2)
{
	this->x = p2.x - p1.x;
	this->y = p2.y - p1.y;
	this->z = p2.z - p1.z;
}

template <class T>
Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

template <class T>
Vector3<T>::Vector3(T xyz) : x(xyz), y(xyz), z(xyz) {}

template <class T>
Vector3<T>::Vector3() : Vector3(0, 0, 0) {}

template <class T>
Vector3<T>::Vector3(const Vector3<T>& other) : Vector3(other.x, other.y, other.z) {}

template <class T>
Vector3<T>& Vector3<T>::operator=(const Vector3<T>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

template <class T>
Vector3<T> Vector3<T>::normalized() const
{
	float magnitude = getMagnitude();
	if (magnitude != 0)
	{
		return (*this / magnitude);
	}
	return Vector3();
}

template <class T>
float Vector3<T>::getMagnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

template <class T>
float Vector3<T>::dotProduct(const Vector3<T>& other) const
{
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

template <class T>
Vector3<T> Vector3<T>::crossProduct(const Vector3<T>& other) const
{
	return Vector3((this->y * other.z) - (this->z * other.y),
		(this->z * other.x) - (this->x * other.z),
		(this->x * other.y) - (this->y * other.x));
}

template <class T>
Vector3<T> Vector3<T>::operator+() const
{
	return *this;
}

template <class T>
Vector3<T> Vector3<T>::operator-() const
{
	return Vector3(-this->x, -this->y, -this->z);
}

template <class T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	return *this;
}

template <class T>
const Vector3<T> Vector3<T>::Zero()
{
	return Vector3<T>(0);
}

template <class T>
std::ostream& operator<<(std::ostream& stream, const Vector3<T>& vector)
{
	return stream << "[" << vector.x << ", " << vector.y << ", " << vector.z << "]";
}

typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;

template <class T>
Vector3<T> operator*(const Vector3<T>& left, const Vector3<T>& right)
{
	return { left.x * right.x, left.y * right.y, left.z * right.z };
}

template <class T>
Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
{
	return { left.x + right.x, left.y + right.y, left.z + right.z };
}

template <class T>
Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right)
{
	return { left.x - right.x, left.y - right.y, left.z - right.z };
}

template <class T>
Vector3<T> operator*(const T& left, const Vector3<T>& right)
{
	return { left * right.x, left * right.y, left * right.z };
}

template <class T>
Vector3<T> operator+(const T& left, const Vector3<T>& right)
{
	return { left + right.x, left + right.y, left + right.z };
}

template <class T>
Vector3<T> operator*(const Vector3<T>& left, const T& right)
{
	return { left.x * right, left.y * right, left.z * right };
}

template <class T>
Vector3<T> operator+(const Vector3<T>& left, T& right)
{
	return { left.x + right, left.y + right, left.z + right };
}

template <class T>
Vector3<T> operator/(const Vector3<T>& left, const float& right)
{
	return { left.x / right, left.y / right, left.z / right };
}