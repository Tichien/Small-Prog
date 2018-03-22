 #include "ConsoleScreen.h"

ConsoleScreen* ConsoleScreen::m_screen = NULL;

ConsoleScreen::ConsoleScreen() : Window(stdscr) {}

ConsoleScreen::~ConsoleScreen() {
	delete m_screen;
}

ConsoleScreen* ConsoleScreen::getInstance(){
	if(!m_screen){
		m_screen = new ConsoleScreen();
	}
	return m_screen;
}
