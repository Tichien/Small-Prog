#pragma once
#include "Rect.h"

class Rectangular{
public:
	virtual ~Rectangular() {}
	virtual Rect getRect() const = 0;
};