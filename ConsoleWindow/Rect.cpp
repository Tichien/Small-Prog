#include "Rect.h"

Rect::Rect() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

Rect::Rect(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Rect::Rect(const Vector2i& position, const Vector2i& size) : Rect(position.x, position.y, size.x, size.y) { }

Rect::Rect(const Rect& rect) : Rect(rect.x, rect.y, rect.width, rect.height) { }

bool Rect::contains(int pointX, int pointY) {
	return pointX >= x && pointX <= width && pointY >= y && pointY <= height;
}

bool Rect::contains(const Vector2i& point) {
	return contains(point.x, point.y);
}

bool Rect::intersects(const Rect& rect) {
	return !(rect.x >= x + width || rect.x + rect.width <= x ||
		rect.y >= y + height || rect.y + rect.height <= y);
}

bool Rect::intersects(const Rect& rect, Rect& intersection) {

	if (intersects(rect)) {
		int xmin = std::max(x, rect.x);
		int xmax = std::min(x + width, rect.x + rect.width);
		int ymin = std::max(y, rect.y);
		int ymax = std::min(y + height, rect.y + rect.height);

		intersection = Rect(xmin, ymin, xmax - xmin, ymax - ymin);
		return true;
	}
	return false;
}

bool operator==(const Rect& left, const Rect& right) {
	return left.x == right.x && left.y == right.y && left.width == right.width && left.height == right.height;
}

bool operator!=(const Rect& left, const Rect& right) {
	return !(left == right);
}