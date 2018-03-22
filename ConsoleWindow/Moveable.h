#pragma once
#include "Vector2.h"

class Moveable
{
public:
	virtual ~Moveable();
	
	virtual void setPosition(int x, int y) = 0;
	void setPosition(const Vector2i& position);

	virtual Vector2i getPosition() const = 0;

	void move(int offsetX, int offsetY);
	void move(Vector2i offset);
};