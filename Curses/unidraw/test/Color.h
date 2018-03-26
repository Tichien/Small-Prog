#ifndef _COLOR_H_
#define _COLOR_H_

extern "C"{
#include <ncursesw/curses.h>
}

enum ColorUnit{
	Default = -1, //La couleur par default du terminal a l'initialisation de ncurses
	
	Black = COLOR_BLACK,
	White = COLOR_WHITE,

	Red = COLOR_RED,
	Green = COLOR_GREEN,
	Blue = COLOR_BLUE,
		
	Cyan = COLOR_CYAN,
	Magenta = COLOR_MAGENTA,
	Yellow = COLOR_YELLOW
};

class ColorPair
{
public:
	ColorUnit front;
	ColorUnit back;

	ColorPair();
	ColorPair(chtype);
	ColorPair(ColorUnit front_back);
	ColorPair(ColorUnit front, ColorUnit back);

	operator chtype() const;

	static const ColorPair Default;
	static const ColorPair WhiteBlack;
	static const ColorPair WhiteRed;
	static const ColorPair WhiteGreen;
	static const ColorPair WhiteBlue;
	static const ColorPair WhiteMagenta;
	static const ColorPair WhiteYellow;
	static const ColorPair WhiteCyan;

	static const ColorPair White;
	static const ColorPair Black;
	static const ColorPair Red;
	static const ColorPair Green;
	static const ColorPair Blue;
	static const ColorPair Magenta;
	static const ColorPair Yellow;
	static const ColorPair Cyan;
};

/* Initialise toutes les pairs de couleurs possible en fonction du terminal */
void init_color_pairs();

/* Change les valeurs de rouge vert et bleu associée à une couleur */
void color_unit_rgb(ColorUnit color, short r, short g, short b);

/* Renvoie le numéro correspondant à la paire de couleur composée de front et back */
int colot_pair_num(ColorUnit front, ColorUnit back);

/* Convertie la paire de couleur composée de front et back en chtype */
chtype color_pair_to_chtype(ColorUnit front, ColorUnit back);

#endif
