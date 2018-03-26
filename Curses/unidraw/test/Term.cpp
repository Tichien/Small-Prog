#include "Term.h"

TermScreen* TermScreen::m_screen = NULL;

TermScreen::TermScreen() : Window(stdscr) {}

TermScreen::~TermScreen() {
	delete m_screen;
}

TermScreen* TermScreen::getInstance(){
	if(!m_screen){
		m_screen = new TermScreen();
	}
	return m_screen;
}


Window Term::scr(NULL); 

void Term::init_curs() {

	setlocale(LC_ALL, "");

	initscr();    // initialize curses

	init_color_pairs(); // initialize colors for the Term if compatible

	Term::scr = *TermScreen::getInstance();

	/*
	screen.setInteractiveModeEnabled(true);
	screen.setSpecialKeySignalEnabled(true);
	screen.setMouseSignalEnabled(true);
	screen.setScrollingEnabled(true);
	screen.setInputDelay(0);
	screen.setCursorVisibility(0);
	screen.fill(screen.getColor(), screen.getAttribute());
	*/
}

void Term::end_curs(){
	endwin();
}

void Term::save_state(){
	def_prog_mode();// Save the tty modes
}

void Term::load_state(){
	reset_prog_mode(); // Return to the previous tty mode
}

void Term::update(){
	doupdate();
}
