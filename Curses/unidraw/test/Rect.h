#ifndef _RECT_H_
#define _RECT_H_

#include "Vector2.h"
#include <algorithm>

////////////////////////////////////////////////// CLASS RECT @@@@@@@@@@

template <typename T>
class Rect {

public:

	T x;
	T y;
	T width;
	T height;

	Rect();

	Rect(T xywh);
	
	Rect(T x, T y, T width, T height);
	
	Rect(const Vector2<T>& position, const Vector2<T>& size);

   	template <typename U>
	explicit Rect(const Rect<U>& rectangle);

	bool contains(T x, T y)  const;

	bool contains(const Vector2<T>& point) const;

	bool intersects(const Rect<T>& rect) const;

	bool intersects(const Rect<T>& rect, Rect<T>& intersection) const;
};

////////////////////////////////////////////////// TYPES COMMUNS

typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;

////////////////////////////////////////////////// CONSTRUCTEURS

template <typename T>
Rect<T>::Rect() : x(), y(), width(), height() {}

template <typename T>
Rect<T>::Rect(T xywh) : x(xywh), y(xywh), width(xywh), height(xywh) {}

template <typename T>
Rect<T>::Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) {}

template <typename T>
Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size) {}

template <typename T>
template <typename U>
Rect<T>::Rect(const Rect<U>& rectangle) : x(rectangle.x), y(rectangle.y), width(rectangle.width), height(rectangle.height) {}

////////////////////////////////////////////////// METHODES

template <typename T>
bool Rect<T>::contains(T x, T y)  const {
	return x >= this->x && x <= width && y >= this->y && y <= height;
}

template <typename T>
bool Rect<T>::contains(const Vector2<T>& point) const {
	return contains(point.x, point.y);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& rect) const {
	return !(rect.x >= x + width || rect.x + rect.width <= x ||
		rect.y >= y + height || rect.y + rect.height <= y);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& rect, Rect<T>& intersection) const {
	if (intersects(rect)) {

		int xmin = std::max(x, rect.x);
		int ymin = std::max(y, rect.y);
		int xmax = std::min(x + width, rect.x + rect.width);
		int ymax = std::min(y + height, rect.y + rect.height);

		intersection = Rect(xmin, ymin, xmax - xmin, ymax - ymin);
		return true;
	}
	return false;
}

////////////////////////////////////////////////// OPERATEURS

template <typename T>
bool operator==(const Rect<T>& left, const Rect<T>& right){
	return left.x == right.x && left.y == right.y && left.width == right.width && left.height == right.height;
}

template <typename T>
bool operator!=(const Rect<T>& left, const Rect<T>& right){
	return !(left == right);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Rect<T>& rect){
	os << "{" << rect.x << ", " << rect.y << ", " << rect.width << ", " << rect.height << "}";
	return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Rect<T>& rect){
  is >> rect.x >> rect.y >> rect.width >> rect.height;
  return is;
}

#endif