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
	
	Window w(newwin(20, 20, 10, 10));

	printw("C'est du text pour tester ");

	Cell cell(L'¤', ColorPair::Red, Attr::Bright);

	w.set_on(ColorPair::Cyan);

	w.set_border(Window::Dash);
	
	w.set_cell(Vector2i(10, 10), cell);

	mvwprintw(w, 0, 0, "Test ma subwin");

	//w.set_border(Window::Dash);
	w.set_off(ColorPair::Cyan);

	w.fill(cell);

	//refresh();

	wgetch(w); //refresh stdscr egalement


	Term::end_curs();

	return 0;
}