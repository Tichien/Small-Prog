#include "Cell.h"

Cell::Cell() : character(L' '), color(), attr() {}

Cell::Cell(cchar_t c) : character(c.chars[0]), color(c.attr), attr(c.attr) {}

Cell::Cell(wint_t character, ColorPair color, Attr attr) : character(character), color(color), attr(attr) {} 

Cell::operator cchar_t() const{

	cchar_t c = { 0, {0, 0, 0, 0, 0}};

	c.attr = attr | color;

	c.chars[0] = character;
	c.chars[1] = L'\0';

	return c;
}