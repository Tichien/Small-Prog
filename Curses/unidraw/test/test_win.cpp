#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED // pour utilisé les fonction wide character et cchar_t
#endif

#include <iostream>
#include "Term.h"

using namespace std;

void check_color(ColorPair col){
	if(col == ColorPair::Default)
		printw("Default\n");
	else if(col == ColorPair::White)
		printw("White\n");
	else if(col == ColorPair::Black)
		printw("Black\n");
	else if(col == ColorPair::Red)
		printw("Red\n");
	else if(col == ColorPair::Green)
		printw("Green\n");
	else if(col == ColorPair::Blue)
		printw("Blue\n");
	else if(col == ColorPair::Magenta)
		printw("Magenta\n");
	else if(col == ColorPair::Cyan)
		printw("Cyan\n");
	else if(col == ColorPair::Yellow)
		printw("Yellow\n");
	else 
		printw("Autre\n");

}

int main()//int argc, char const *argv[])
{

	Term::init_curs();

	//Window w = Term::scr;
	
	Window w(stdscr);
	/*
    setlocale(LC_ALL, "");
    initscr();

    init_color_pairs();
	
	refresh();
	
	
	*/

	Cell cell(L'¤', ColorPair::Red, Attr::Bright);

	w.set_on(ColorPair::Cyan);
	
	w.set_border(Window::Dash);
	w.set_off(ColorPair::Cyan);

	/*
	wprintw(w, "dimension : %d, %d\n", w.get_dimension().x, w.get_dimension().y);
	
	if(can_change_color())
		wprintw(w, "couleurs modifiable");
	else
		wprintw(w, "couleurs non modifiable");
*/
/*
	w.set_cell(Vector2i(10, 10), cell);

	w.set_color(ColorPair::Red);

	mvwprintw(w, 30, 30, "Test couleurs bleu soulignées");

	w.set_background(Cell(L'-'));


	mvwprintw(w, 31, 30, "nouveau back ground ajouté");
*/
	//w.fill(ColorPair::Magenta, Attr::Bright);

	//w.clear();

	//Term::scr
	//refresh();
	//getch(); //refresh stdscr egalement
	//w.display();
	//doupdate();

	Term::end_curs();

	return 0;
}