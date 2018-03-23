/*
Quelques outils de dessin pour le terminal 
grandement inspiré de SFML et de DRAWILLE 
*/

#ifndef _UNIDRAW_H_
#define _UNIDRAW_H_

#include <iostream>
#include <sstream>
#include <algorithm>

#include <clocale>
#include <cwchar>

extern "C"{
#include <ncursesw/curses.h>
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS VECTOR2

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

	static Vector2<T> zero;
	static Vector2<T> one;
	static Vector2<T> up;
	static Vector2<T> down;
	static Vector2<T> left;
	static Vector2<T> right;
};

////////////////////////////////////////////////// TYPES COMMUNS

typedef Vector2<int> 			Vector2i;
typedef Vector2<unsigned int> 	Vector2u;
typedef Vector2<float> 			Vector2f;

////////////////////////////////////////////////// VARIABLE STATIQUES

template <typename T>
Vector2<T> Vector2<T>::zero(0, 0);

template <typename T>
Vector2<T> Vector2<T>::one(1, 1);

template <typename T>
Vector2<T> Vector2<T>::up(0, -1);

template <typename T>
Vector2<T> Vector2<T>::down(0, 1);

template <typename T>
Vector2<T> Vector2<T>::left(-1, 0);

template <typename T>
Vector2<T> Vector2<T>::right(1, 0);

////////////////////////////////////////////////// CONSTRUCTEURS

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

////////////////////////////////////////////////// METHODES


////////////////////////////////////////////////// OPERATEURS

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

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS RECT

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
Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size) : x(position.x), y(position.y), width(size.x), height(size.y) {}

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

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS CANVAS

class Canvas {

public:
	WINDOW* m_frame;

public:
	Canvas();
	Canvas(int w, int h);
	virtual ~Canvas();

	void set(int x, int y);
	void set(const Vector2i& point);
	
	void unset(int x, int y);
	void unset(const Vector2i& point);
	
	void toggle(int x, int y);
	void toggle(const Vector2i& point);

	wint_t get_cell(int row, int col) const;
	wint_t get_cell(const Vector2i& cell_coord) const;

	void set_cell(int row, int col, wint_t c);
	void set_cell(const Vector2i& cell_coord, wint_t c);

	/* Renvoie les dimension du canvas en nombre de pixel (width, height) */
	Vector2i get_size() const;

	/* Renvoie les dimension du canvas en nombre de cellules (row, col) */
	Vector2i get_cells_size() const;

	void write(int x, int y, const std::string& text);
	void write(const Vector2i& position, const std::string& text);

	void clear(int col = 0, int row = 0, int w = 0, int h = 0);

	void display();
	void display(const Vector2i& position, const IntRect& offset);

	bool is_set(int x, int y);
};

/* Converti les coordonnées du pixel (x, y) en coordonnée de cellule (row, col) */
Vector2i pixel_to_cell_coord(int x, int y);
Vector2i pixel_to_cell_coord(const Vector2i& point);

/* Converti les coordonnées de la cellule (row, col) en coordonnée de pixel (x, y) */
Vector2i cell_to_pixel_coord(int row, int col);
Vector2i cell_to_pixel_coord(const Vector2i& cell_coord);

bool is_braille(wint_t cell);

void draw_line(Canvas& canvas, int x1, int y1, int x2, int y2);
void draw_line(Canvas& canvas, const Vector2i& p1, const Vector2i p2);

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS CANVAS

class Turtle
{
private:
	Canvas* m_canvas;
	Vector2i position;
	float rotation;
	bool write;

	bool allocated;

public:
	Turtle();
	Turtle(Canvas* canvas);
	~Turtle();

	void draw(float distance);

	/* Renvoie la position d'origine de la tortue */
	void move(float distance);

	void turn(float angle);
};

void draw_polygon(Canvas& c, float length, int sides);

#endif