#include "Console.h"

Window Console::Screen; 

void Console::startPowerMode() {

	initscr();    // initialize curses
	initColors(); // initialize colors for the console if compatible
	Screen = *ConsoleScreen::getInstance();
	Screen.setInteractiveModeEnabled(true);
	Screen.setSpecialKeySignalEnabled(true);
	Screen.setMouseSignalEnabled(true);
	Screen.setScrollingEnabled(true);
	Screen.setInputDelay(0);
	Screen.setCursorVisibility(0);
	Screen.fill(Screen.getColor(), Screen.getAttribute());
}

void Console::endPowerMode() {
	endwin();
}

void Console::saveState() {
	//or savetty()
	def_prog_mode(); // Save the tty modes
}

void Console::loadState() {
	//or resettty()
	reset_prog_mode(); // Return to the previous tty mode
}

void Console::update() { 
	doupdate();
}