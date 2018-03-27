#include "Term.h"

TermScreen* TermScreen::m_screen = NULL;

TermScreen::TermScreen() : Window(stdscr) {}

TermScreen::~TermScreen() {
	//delete m_screen;
}

TermScreen* TermScreen::getInstance(){
	if(!m_screen){
		m_screen = new TermScreen();
	}
	return m_screen;
}

Window Term::scr; 

//int (*Term::scan)(const char*, ...) = scanw; 

void Term::init_curs() {

	setlocale(LC_ALL, "");

	initscr();    // initialize curses

	init_color_pairs(); // initialize colors for the Term if compatible

	Term::scr = *TermScreen::getInstance();

	scr.set_special_key(true);
	scr.set_input_timeout(-1); //-1 block the program if no input detected
	
	Term::cooked_mode(false);
	Term::echo_key(false);
	Term::curs_vis(0);

	refresh();
}

void Term::end_curs(){
	endwin();
}

void Term::save_state(){
	def_prog_mode();// Save the ncurses win (!= savetty)
}

void Term::load_state(){
	reset_prog_mode(); // reset the ncurses win (!= resetty)
}

void Term::cooked_mode(bool on){
	on ? nocbreak() : cbreak();
}

void Term::echo_key(bool on){
	on ? echo() : noecho();
}

void Term::curs_vis(int vis){
	curs_set(vis);
}

void Term::wait(int ms){
	napms(ms);
}

int Term::pop_input(){
	return getch();
}

void Term::push_input(int ch){
	ungetch(ch); 
}

void Term::getline(std::string& str){
	char cstr[1024] = "";
	getstr(cstr);
	str = cstr;
}

void Term::update(){
	doupdate();
}


