#pragma once
#include "Color.h"
#include "Attribute.h"

class Cellule
{
public:
	chtype chartext;
	ConsoleColor color;
	Attribute attribute;

	Cellule();
	Cellule(chtype);
	Cellule(chtype c, ConsoleColor col, Attribute attr = Attribute::Bold);
	operator chtype() const;
};