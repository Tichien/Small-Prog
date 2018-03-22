#pragma once

extern "C" {
#include "curses.h"
}

enum SimpleColor {
	Black = COLOR_BLACK,
	
	Red = COLOR_RED,
	Green = COLOR_GREEN,
	Blue = COLOR_BLUE,
		
	Cyan = COLOR_CYAN,
	Magenta = COLOR_MAGENTA,
	Yellow = COLOR_YELLOW,

	White = COLOR_WHITE,

	Transparent,
};

class ConsoleColor
{
public:
	SimpleColor front;
	SimpleColor back;

	ConsoleColor();
	ConsoleColor(chtype);
	ConsoleColor(SimpleColor front, SimpleColor back);

	operator chtype() const;

	static const ConsoleColor WhiteBlack;
	static const ConsoleColor WhiteRed;
	static const ConsoleColor WhiteGreen;
	static const ConsoleColor WhiteBlue;
	static const ConsoleColor WhiteMagenta;
	static const ConsoleColor WhiteYellow;
	static const ConsoleColor WhiteCyan;
	static const ConsoleColor Default;
};


void initColors();
chtype getColorPair(SimpleColor front, SimpleColor back);
int getPairNumber(SimpleColor front, SimpleColor back);
