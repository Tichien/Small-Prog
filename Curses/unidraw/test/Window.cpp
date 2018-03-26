#include "Window.h"

Window::Window(WINDOW* win) : m_win(win) {
	//m_win = win;
	//int x = 0, y = 0;
	//getmaxyx(win, y, x);
	//setSize(x, y);
}

Window::~Window() {
	delwin(m_win);
}

Vector2i Window::get_dimension() const{
	int x = 0, y = 0;
	getmaxyx(m_win, y, x);
	return Vector2i(x, y);
}

void Window::set_dimension(const Vector2i& dim){
	if(dim.x >= 0 && dim.y >= 0){
		//m_size = Vector2i(width, height);
/*
		WINDOW* win = newpad(height, width);

		wbkgd(win, m_color | m_attribute);

		overwrite(m_win, win);

		wresize(m_win, height, width);

		overwrite(win, m_win);

		delwin(win);
		*/
	}
}

Vector2i Window::get_curs_pos() const{
	int x = 0, y = 0;
	getyx(m_win, y, x);
	return Vector2i(x, y);
}

void Window::set_curs_pos(const Vector2i& pos){
	wmove(m_win, pos.y, pos.x);
}

Cell Window::get_cell(const Vector2i& coord) const{
	cchar_t c;
	wmvin_wch(m_win, coord.y, coord.x, &c);
	return Cell(c);
}

void Window::set_cell(const Vector2i& coord, Cell cell){
	cchar_t c = cell;

	wattron(m_win, c.attr)
	mvwaddnwstr(m_win, coord.y, coord.x, c.chars, 1);
	wattroff(m_win, c.attr);
}

void Window::set_cell(const Vector2i& coord, wint_t wchar, ColorPair color, Attr attr){
	set_cell(coord, wchar, color, attr);
}

Attr Window::get_attr() const{
	chtype attr;
	wattr_get(m_win, &attr, NULL, NULL);
	return Attr(attr);
}

void Window::set_attr(Attr attr){ /* Continuer ici */
	chtype at = attr = ;
	wattr_get(m_win, &attr, NULL, NULL);
	return Attr(attr);
} //wattr_get

/* return/set the Window's color pair when writing */
ColorPair Window::get_color() const{

}

void Window::set_color(ColorPair){

}

/* set on/off a Window's attribute and/or Color can be or'd with | */
void Window::set_on(chtype attr_color){

}

void Window::set_off(chtype attr_color){

}

/* return the data of the Window in one wide string */
std::wstring Window::to_wstring(){

}

/* draw a border around the window */
void Window::set_border(BorderType type, ColorPair color, Attr attr){

} //verifier pas de problème avec assignation par default

void Window::set_border(Cell left, Cell right, Cell up, Cell down, Cell upLeft, Cell upRight, Cell downLeft, Cell downRight){

}


/* fill the windows whith a specific Cell, ColorPair and/or Attribute */
void Window::fill(Cell){

}

void Window::fill(ColorPair color, Attr attr){

} 


/* copy the content of another Window */
void Window::copy(const Window&, const IntRect&, const Vector2i&, bool convert_attr){

}


void Window::write(const Vector2i& coord, std::wstring, ColorPair color, Attr attr){

}


/* clear the Window */
void Window::clear(){

} //

/* prepare the Window to be drawn at the next Term::update */
void Window::display(){

} //
