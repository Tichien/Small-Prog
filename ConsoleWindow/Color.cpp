#include "Color.h"

ConsoleColor::ConsoleColor() : front(White), back(Black) {}

ConsoleColor::ConsoleColor(chtype c){
	short f = 0, b = 0;
	PAIR_NUMBER(c);
	pair_content(PAIR_NUMBER(c), &f, &b);
	front = (SimpleColor)f;
	back = (SimpleColor)b;
}

ConsoleColor::ConsoleColor(SimpleColor front, SimpleColor back) {
	this->front = front;
	this->back = back;
}

ConsoleColor::operator chtype() const{
	return getColorPair(front, back);
}

const ConsoleColor ConsoleColor::WhiteBlack(White, Black);
const ConsoleColor ConsoleColor::WhiteRed(White, Red);
const ConsoleColor ConsoleColor::WhiteGreen(White, Green);
const ConsoleColor ConsoleColor::WhiteBlue(White, Blue);
const ConsoleColor ConsoleColor::WhiteMagenta(White, Magenta);
const ConsoleColor ConsoleColor::WhiteYellow(White, Yellow);
const ConsoleColor ConsoleColor::WhiteCyan(White, Cyan);
const ConsoleColor ConsoleColor::Default(White, Black);

void initColors() {
	if (has_colors()) {

		start_color();
		use_default_colors();

		for (int j = 0; j < COLORS; ++j)
		{
			for (int i = 0; i < COLORS; ++i)
			{
				init_pair(j * COLORS + i, j, i);
			}
		}
	}
}

chtype getColorPair(SimpleColor front, SimpleColor back) {
	return COLOR_PAIR(getPairNumber(front, back));
}

int getPairNumber(SimpleColor front, SimpleColor back) {
	return front * COLORS + back;
}
