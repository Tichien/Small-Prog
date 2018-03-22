#pragma once
#include "Vector2.h"
#include <algorithm>

class Rect {

public:
	int x;
	int y;
	int width;
	int height;

	Rect();
	Rect(int x, int y, int width, int height);
	Rect(const Vector2i& position, const Vector2i& size);
	Rect(const Rect& rect);

	bool contains(int pointX, int pointY);
	bool contains(const Vector2i& point);

	bool intersects(const Rect& rect);
	bool intersects(const Rect& rect, Rect& intersection);
};

bool operator==(const Rect& left, const Rect& right);
bool operator!=(const Rect& left, const Rect& right);