#include <iostream>
#include "Term.h"

using namespace std;

void handler();

int main()
{
	Term::init_curs();

	int ch = 0;
	
	while(!Keyboard::is_pressed(Keyboard::Escape)){

		Term::read_input();

		Term::clear();

	    mvprintw(0, 0, "Mouse position : %d, %d", Mouse::get_position().x, Mouse::get_position().y);
	    mvprintw(1, 0, "Mouse bstate : %lu", Mouse::event.bstate);
	    mvprintw(2, 0, "Key : %d", Keyboard::input);

	    handler();
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
