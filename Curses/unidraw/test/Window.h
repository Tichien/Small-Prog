#ifndef _WINDOW_H_
#define _WINDOW_H_

/*
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED // pour utilisé les fonction wide character et cchar_t
#endif
*/
#include <string>
#include "Rect.h"
#include "Cell.h"


//La class Window permet d'englober les WINDOW*. 
//Pour englober les PADs il faudra redefinir la methode display avec pnoutrefresh */
class Window {

protected:

	WINDOW* m_win;
	Window(WINDOW* win);

public:

	enum BorderType {
		Empty,
		Thin,
		Point,
		Dash,
		Block,
		Diamond,
		Board,
		CheckBoard,
		Arrow,
	};

	Window();
	virtual ~Window();

	operator WINDOW*();

/* return/set the dimension of the Window (col, row) (stdscr ne peut pas  être resize et rien ne peut etre plus grand que stdscr a par les pads) */
	Vector2i get_dimension() const;
	//void set_dimension(const Vector2i& dim);

/* return/set the cursor position relative to up-left corner of the Window (col, row) */
	Vector2i get_curs_pos() const;
	void set_curs_pos(const Vector2i& coord);

/* return an input, pop it from the input queue and refresh the window */
	int pop_input();

/*  set a timeout while waiting for input -(1 => wait for input)*/
	void set_input_timeout(int ms);

/* enable special key like arrows, f1, f2, etc... */
	void set_special_key(bool);

/* return/set a Window's cell relative to up-left corner of the window (col, row) */
	Cell get_cell(const Vector2i& coord) const;
	void set_cell(const Vector2i& coord, const Cell& cell);
	void set_cell(const Vector2i& coord, wint_t wchar, ColorPair color = ColorPair::Default, Attr attr = Attr::Normal);

/* return/set the Window's attribute when writing */
	Attr get_attr() const; //wattr_set
	void set_attr(Attr); //wattr_get

/* return/set the Window's color pair when writing */
	ColorPair get_color() const;
	void set_color(ColorPair);

/* set on/off a Window's attribute and/or Color can be or'd with | */
	void set_on(chtype attr_color);
	void set_off(chtype attr_color);

/* return the data of the Window in one wide string */
	std::wstring to_wstring() const;

/* draw a border around the window */
	void set_border(BorderType type, ColorPair c = ColorPair::Default, Attr  a = Attr::Normal); //verifier pas de problème avec assignation par default
	void set_border(Cell left, Cell right, Cell up, Cell down, Cell upLeft, Cell upRight, Cell downLeft, Cell downRight);

/* fill the windows background whith a specific Cell, ColorPair and/or Attribute */
	void fill(const Cell&);
	void fill(ColorPair color, Attr attr = Attr::Normal); 

/* return/set the windows background whith a specific Cell, ColorPair and/or Attribute */
	Cell get_background() const;
	void set_background(const Cell&);
	void set_background(ColorPair color, Attr attr = Attr::Normal); 

/* copy the content of another Window */
	//void copy(const Window&, const IntRect&, const Vector2i&, bool convert_attr = true);// copywin;

	//void write(std::wstring, ColorPair color = ColorPair::Default, Attr attr = Attr::Normal);
	//void write(const Vector2i& coord, std::wstring, ColorPair color = ColorPair::Default, Attr attr = Attr::Normal);

/* clear the Window */
	void clear();
	void clear(const IntRect& zone);

/* prepare the Window to be drawn at the next Term::update */
	virtual void display(); //pnoutrefresh;
};

#endif
