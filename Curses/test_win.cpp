#include <iostream>
#include "Term.h"
#include "Mouse.h"

using namespace std;

void handler(Window& w);

int main()//int argc, char const *argv[])
{
	Term::init_curs();
	
	cbreak();
    noecho();
   	//curs_set(0); /* Invisible cursor */
   	halfdelay(0); /* Don't wait for more than 1/10 seconds for a keypress */
    keypad(stdscr, TRUE); /* Enable keypad mode */
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL); /* Report all mouse events */
	//mouseinterval(0);
    int ch  = 0;
    int event_num = 0;

	while((ch = getch()) != 'q'){

		//clear();

    /*
		if(Mouse::isButtonPressed(Mouse::Button::Left))
			mvprintw(0, 0, "Mouse position : %d, %d", Mouse::getPosition().x, Mouse::getPosition().y);
	*/
   		if(ch == KEY_MOUSE){
   			
   			MEVENT event;

   			event_num++;

	    	if(getmouse(&event) == OK)
	    		mvprintw(0, 0, "Mouse position : %d, %d", event.x, event.y);
	    	else
	    		mvprintw(0, 0, "Mouse event error");

	    	mvprintw(1, 0, "Event count : %d", event_num);
   		}


		refresh();
	}

	Term::end_curs();

	return 0;
}

/*
void handler(Window& w){

	if(Keyboard::isKeyPressed(Keyboard::Key::Z)){
	
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Q)){
	
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::S)){ 
	
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::D)){
	
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Up)){
	
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Left)){

	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Down)){

	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Right)){

	}
	else if(Mouse::isButtonPressed(Mouse::Button::Right)){

	}
	else if(Mouse::isButtonPressed(Mouse::Button::Left)){

	}
}
*/