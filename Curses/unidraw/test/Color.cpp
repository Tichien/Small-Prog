#include "Color.h"

ColorPair::ColorPair() : front(ColorUnit::Default), back(ColorUnit::Default) {}

ColorPair::ColorPair(chtype c){

	chtype color = c & A_COLOR;
	short f = 0, b = 0;

	pair_content(PAIR_NUMBER(color), &f, &b);

	front = (ColorUnit)f;
	back = (ColorUnit)b;
}

ColorPair::ColorPair(ColorUnit front_back){
	front = front_back;
	back = front_back;
}

ColorPair::ColorPair(ColorUnit front, ColorUnit back) {
	this->front = front;
	this->back = back;
}

ColorPair::operator chtype() const{
	
	return color_pair_to_chtype(front, back);
}

const ColorPair ColorPair::Default(ColorUnit::Default, ColorUnit::Default);
const ColorPair ColorPair::WhiteBlack(ColorUnit::White, ColorUnit::Black);
const ColorPair ColorPair::WhiteRed(ColorUnit::White, ColorUnit::Red);
const ColorPair ColorPair::WhiteGreen(ColorUnit::White, ColorUnit::Green);
const ColorPair ColorPair::WhiteBlue(ColorUnit::White, ColorUnit::Blue);
const ColorPair ColorPair::WhiteMagenta(ColorUnit::White, ColorUnit::Magenta);
const ColorPair ColorPair::WhiteYellow(ColorUnit::White, ColorUnit::Yellow);
const ColorPair ColorPair::WhiteCyan(ColorUnit::White, ColorUnit::Cyan);

const ColorPair ColorPair::White(ColorUnit::White, ColorUnit::Default);
const ColorPair ColorPair::Black(ColorUnit::Black, ColorUnit::Default);
const ColorPair ColorPair::Red(ColorUnit::Red, ColorUnit::Default);
const ColorPair ColorPair::Green(ColorUnit::Green, ColorUnit::Default);
const ColorPair ColorPair::Blue(ColorUnit::Blue, ColorUnit::Default);
const ColorPair ColorPair::Magenta(ColorUnit::Magenta, ColorUnit::Default);
const ColorPair ColorPair::Yellow(ColorUnit::Yellow, ColorUnit::Default);
const ColorPair ColorPair::Cyan(ColorUnit::Cyan, ColorUnit::Default);


void init_color_pairs(){

	if (has_colors()) {

		start_color();

		use_default_colors(); // -> COLOR_PAIR(0) = DefaultColor

		for (int j = 0; j < COLORS; ++j)
		{
			for (int i = 0; i < COLORS; ++i)
			{
				//init_pair(numero, front, back) (-1 correspond à la couleur par default du terminal)
				init_pair(j * COLORS + i + 1, j - 1, i - 1);
			}
		}
	}
}

int colot_pair_num(ColorUnit front, ColorUnit back) {
	return (front + 1) * COLORS + (back + 1) + 1;
}

chtype color_pair_to_chtype(ColorUnit front, ColorUnit back) {
	return COLOR_PAIR(colot_pair_num(front, back));
}