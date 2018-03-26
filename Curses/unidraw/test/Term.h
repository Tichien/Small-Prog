#ifndef _TERM_H_
#define _TERM_H_

#include "Window.h"

class TermScreen : public Window {

private:
	static TermScreen* m_screen;

	TermScreen();
	TermScreen(const TermScreen&);
	TermScreen& operator=(const TermScreen&);

public:
	static TermScreen* getInstance();
	~TermScreen();
};

class Term {

public:
	static Window scr;

	static void init_curs();
	static void end_curs();

	static void save_state();
	static void load_state();

	static void update();

	static void cooked_mode(bool);// cbreak();
	static void echo_key(bool);// echo();
	static void special_key(bool);// keypad();
	//static void scroll(bool);// scrollok();

	static int get_timeout();
	static void set_timeout();

	static void set_curs_vis(int vis);

	static int pop_input(); //getch()
	static void push_input(); //ungetch()

	static void getline(); //getstr()
};

#endif