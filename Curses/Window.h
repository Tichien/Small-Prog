#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Rect.h"
#include "Cell.h"

//#PREPROCESSING
#include <string>
//#PREPROCESSING_END

//#DECLARATION
/* Cette class permet d'englober la structure WINDOW* definie dans ncurses. */ 

class Window {

protected:

	WINDOW* m_win;
	Window(WINDOW* win);

public:

	enum BorderType {
		Empty,
		Thin,
		ThinRound,
		Thick,
		Double,
		Block,
		BlockShade,
		Dash,
		Diamond,
		Point,
		PointThick,
		Snow,
		SnowThick
	};

	Window();
	virtual ~Window();

	operator WINDOW*();

/* return the dimensions of the Window (col, row) (stdscr ne peut pas  être resize et rien ne peut etre plus grand que stdscr a par les pads) */
	Vector2i get_dimension() const;
	//void set_dimension(const Vector2i& dim);

/* return/set the cursor position relative to up-left corner of the Window (col, row) */
	Vector2i get_curs_pos() const;
	void set_curs_pos(const Vector2i& coord);

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

/* clear the Window */
	void clear();
	void clear(const IntRect& zone);

/* display the window to the virtual screen (use Term::update to display the virtual screen) */
	virtual void display(); //pnoutrefresh;

/* display the window directly to the realscreen without optimisation */
	void refresh();
};

//#DECLARATION_END

#endif
