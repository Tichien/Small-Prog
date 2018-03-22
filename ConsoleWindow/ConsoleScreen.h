#pragma once
#include "Window.h"

class ConsoleScreen : public Window
{
private:
	static ConsoleScreen* m_screen;
	ConsoleScreen();
	ConsoleScreen(const ConsoleScreen&);
	ConsoleScreen& operator=(const ConsoleScreen&);
public:
	static ConsoleScreen* getInstance();
	~ConsoleScreen();
};