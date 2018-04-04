#include <iostream>
#include "Term.h"

using namespace std;

void handler();

int main()//int argc, char const *argv[])
{
	//export TERM=xterm-1003   (push mouse pos) (1002 only on click)
	Term::init_curs();
	
	//cbreak();
    //noecho();
   	//timeout(0);
    keypad(stdscr, TRUE); /* Enable keypad mode */
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL); /* Report all mouse events */
	//mouseinterval(0);

	int ch = 0;
	while((ch = Term::read_input()) != 'q'){

		erase();

	    mvprintw(0, 0, "Mouse position : %d, %d", Mouse::get_pos().x, Mouse::get_pos().y);
	    mvprintw(1, 0, "Mouse bstate : %lu", Mouse::event.bstate);
	    mvprintw(2, 0, "Key : %d", Keyboard::input);

	    handler();

		//refresh();
	}

	Term::end_curs();

	return 0;
}

void handler(){
	if(Mouse::is_pressed(Mouse::Left))
		mvprintw(1, 0, "Left");
	else if(Mouse::is_pressed(Mouse::Right))
		mvprintw(1, 0, "Right");
	else if(Mouse::is_pressed(Mouse::Middle))
		mvprintw(1, 0, "Middle");

	else if(Keyboard::is_pressed(Keyboard::A))
		mvprintw(1, 0, "A");
	else if(Keyboard::is_pressed(Keyboard::Z))
		mvprintw(1, 0, "Z");
	else if(Keyboard::is_pressed(Keyboard::E))
		mvprintw(1, 0, "E");

}
