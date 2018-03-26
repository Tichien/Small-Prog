#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED // pour utilisé les fonction wide character et cchar_t
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <clocale>
#include <cwchar>
#include <curses.h>
#include "Cell.h"


using namespace std;
wint_t braile_num = 0x2801;
wint_t braile_char = L'⠁';

int main(int argc, char const *argv[])
{

	setlocale(LC_ALL, "");

	initscr();

	init_color_pairs();

	Cell cell(L'€', ColorPair::Green, Attr::Bright | Attr::Italic);
	cchar_t c = cell;

	//add_wchnstr(&c, 1);
	attron(c.attr);
	addwstr(c.chars);
	//add_wch(&c);
	addch('e');
	attroff(c.attr);

	cchar_t c2;
	mvin_wch(0, 0, &c2);
	Cell cell2(c2);

	attron(cell2.attr | cell2.color);
	mvprintw(10, 10, "%lc", cell2.character);
	attroff(cell2.attr | cell2.color);


	//refresh();

	getch();

	endwin();
	return 0;
} 