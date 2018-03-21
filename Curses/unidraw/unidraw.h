#ifndef _UNIDRAW_H_
#define _UNIDRAW_H_

#include <cwchar>

extern "C"{
#include <ncursesw/curses.h>
}


class Canvas {

private:
	WINDOW* m_frame;

public:
	Canvas();
	Canvas(int col, int row, int w, int h);
	virtual ~Canvas();

	void set(int x, int y);
	void unset(int x, int y);
	void toggle(int x, int y);

	wint_t getcell(int col, int row);
	void setcell(int col, int row, wint_t c);

	void write(int col, int row, const char* text);
	void clear(int col = 0, int row = 0, int w = 0, int h = 0);
	void display();

	bool is_set(int x, int y);
};

void pixel2cell(int x, int y, int& col, int& row);
bool is_braille(wint_t cell);
void draw(const Canvas& c);
void drawLine(int x1, int y1, int x2, int y2);

#endif