#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <sstream>
#include <fstream>

template <typename T>
class Vector2 {

public:

	T x;
	T y;

	Vector2();

	Vector2(T xy);
	
	Vector2(T x, T y);
	
	template <typename U>
	explicit Vector2(const Vector2<U>& vector);
	
	~Vector2();

	static Vector2<T> Zero;
	static Vector2<T> One;
	static Vector2<T> Up;
	static Vector2<T> Down;
	static Vector2<T> Left;
	static Vector2<T> Right;
};

template <typename T>
Vector2<T> Vector2<T>::Zero(0, 0);

template <typename T>
Vector2<T> Vector2<T>::One(1, 1);

template <typename T>
Vector2<T> Vector2<T>::Up(0, -1);

template <typename T>
Vector2<T> Vector2<T>::Down(0, 1);

template <typename T>
Vector2<T> Vector2<T>::Left(-1, 0);

template <typename T>
Vector2<T> Vector2<T>::Right(1, 0);

template <typename T>
Vector2<T>::Vector2() : x(), y() {}

template <typename T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

template <typename T>
Vector2<T>::Vector2(T xy) : x(xy), y(xy) {}

template <typename T>
template <typename U>
Vector2<T>::Vector2(const Vector2<U> &vector) : x(vector.x), y(vector.y) {}

template <typename T>
Vector2<T>::~Vector2() {}

typedef Vector2<int> 			Vector2i;
typedef Vector2<unsigned int> 	Vector2u;
typedef Vector2<float> 			Vector2f;

template <typename T>
Vector2<T> operator-(const Vector2<T>& right){
	return Vector2<T>(-right.x, -right.y);
}

template <typename T>
Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right){
	left.x += right.x;
	left.y += right.y;
	return left;
}

template <typename T>
Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right){
	left += -right;
	return left;
}

template <typename T>
Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right){
	return Vector2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right){
	return (left + -right);
}

template <typename T>
Vector2<T> operator*(const Vector2<T>& left, T right){
	return Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
Vector2<T> operator*(T left, const Vector2<T>& right){
	return (right * left);
}

template <typename T>
Vector2<T>& operator*=(Vector2<T>& left, T right){
	left.x *= right;
	left.y *= right;
	return left;
}

template <typename T>
Vector2<T> operator/(const Vector2<T>& left, T right){
	return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
Vector2<T>& operator/=(Vector2<T>& left, T right){
	left.x /= right;
	left.y /= right;
	return left;
}

template <typename T>
bool operator==(const Vector2<T>& left, const Vector2<T>& right){
	return left.x == right.x && left.y == right.y;
}

template <typename T>
bool operator!=(const Vector2<T>& left, const Vector2<T>& right){
	return !(left == right);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vector){
	os << "{" << vector.x << ", " << vector.y << "}";
	return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Vector2<T>& vector){
  is >> vector.x >> vector.y;
  return is;
}

#endif