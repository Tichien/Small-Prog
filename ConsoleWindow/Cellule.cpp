#include "Cellule.h"


Cellule::Cellule() {
	chartext = 0;
}

Cellule::Cellule(chtype c) {
	chartext = c;
	color = ConsoleColor(c);
	attribute = Attribute(c);
}

Cellule::Cellule(chtype c, ConsoleColor col, Attribute attr) : chartext(c), color(col), attribute(attr) {} 

Cellule::operator chtype() const{
	return chartext | color | attribute;
}