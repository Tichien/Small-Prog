#pragma once
#include "Vector2.h"

class Resizable
{
public:
	virtual ~Resizable();
	
	virtual void setSize(int width, int height) = 0;
	void setSize(const Vector2i& size);

	virtual Vector2i getSize() const = 0;

	void resize(int offsetX, int offsetY);
	void resize(Vector2i offset);
};