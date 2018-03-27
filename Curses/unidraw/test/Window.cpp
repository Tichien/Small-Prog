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

Window::operator WINDOW*(){
	return m_win;
}

Vector2i Window::get_dimension() const{
	int x = 0, y = 0;
	getmaxyx(m_win, y, x);
	return Vector2i(x, y);
}

void Window::set_dimension(const Vector2i& dim){
 		//(resize est un extension de ncurses)
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
	mvwin_wch(m_win, coord.y, coord.x, &c);
	return Cell(c);
}

void Window::set_cell(const Vector2i& coord, const Cell& cell){

	cchar_t c = cell;

	if(cell.color == ColorPair::Default){
		c.attr |= get_color(); //affiche dans la couleur courante du terminal
	}

	mvwadd_wchnstr(m_win, coord.y, coord.x, &c, 1);
}

void Window::set_cell(const Vector2i& coord, wint_t wchar, ColorPair color, Attr attr){
	set_cell(coord, Cell(wchar, color, attr));
}

Attr Window::get_attr() const{
	attr_t at;
	short pair; 
	
	wattr_get(m_win, &at, &pair, NULL);

	return Attr(at);
}

void Window::set_attr(Attr attr){ 
	attr_t at = attr;
	short pair = get_color().pair_num();
	
	wattr_set(m_win, at, pair, NULL);
}

ColorPair Window::get_color() const{
	attr_t at;
	short pair; 
	
	wattr_get(m_win, &at, &pair, NULL);

	return COLOR_PAIR(pair);
}

void Window::set_color(ColorPair color){
	wcolor_set(m_win, color.pair_num(), NULL);
}

void Window::set_on(chtype attr_color){
	wattron(m_win, attr_color);
}


void Window::set_off(chtype attr_color){
	wattroff(m_win, attr_color);
}

std::wstring Window::to_wstring(){
	std::wstring data;
	wchar_t* wstr = new wchar_t[get_dimension().x];

	for(int i = 0 ; i < get_dimension().y ; i++){

		mvwinwstr(m_win, 0, 0, wstr);
		data += std::wstring(wstr); 
	}
	return data;
}


//fuite memoire dans set border
void Window::set_border(Cell left, Cell right, Cell up, Cell down, Cell upLeft, Cell upRight, Cell downLeft, Cell downRight){
	cchar_t l = left;
	cchar_t r = right;
	cchar_t u = up;
	cchar_t d = down;
	cchar_t ul = upLeft;
	cchar_t ur = upRight;
	cchar_t dl = downLeft;
	cchar_t dr = downRight;

	wborder_set(m_win, &l, &r, &u, &d, &ul, &ur, &dl, &dr);
}

//fuite memoire dans set border
void Window::set_border(BorderType type, ColorPair color, Attr a){

	ColorPair c = color == ColorPair::Default ? get_color() : color;

	switch (type)
	{
		case Empty:
		set_border(Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a));
		break;
		case Thin:
		set_border(Cell(ACS_VLINE, c, a), Cell(ACS_VLINE, c, a), Cell(ACS_HLINE, c, a), Cell(ACS_HLINE, c, a), Cell(ACS_ULCORNER, c, a), Cell(ACS_URCORNER, c, a), Cell(ACS_LLCORNER, c, a), Cell(ACS_LRCORNER, c, a));
		break;
		case Point:
		set_border(Cell(ACS_BULLET, c, a), Cell(ACS_BULLET, c, a), Cell(ACS_BULLET, c, a), Cell(ACS_BULLET, c, a), Cell(ACS_BULLET, c, a), Cell(ACS_BULLET, c, a), Cell(ACS_BULLET, c, a), Cell(ACS_BULLET, c, a));
		break;
		case Dash: 
		set_border(Cell('|', c, a), Cell('|', c, a), Cell('-', c, a), Cell('-', c, a), Cell('+', c, a), Cell('+', c, a), Cell('+', c, a), Cell('+', c, a));
		break;
		case Block:
		set_border(Cell(ACS_BLOCK, c, a), Cell(ACS_BLOCK, c, a), Cell(ACS_BLOCK, c, a), Cell(ACS_BLOCK, c, a), Cell(ACS_BLOCK, c, a), Cell(ACS_BLOCK, c, a), Cell(ACS_BLOCK, c, a), Cell(ACS_BLOCK, c, a));
		break;
		case Diamond:
		set_border(Cell(ACS_DIAMOND, c, a), Cell(ACS_DIAMOND, c, a), Cell(ACS_DIAMOND, c, a), Cell(ACS_DIAMOND, c, a), Cell(ACS_DIAMOND, c, a), Cell(ACS_DIAMOND, c, a), Cell(ACS_DIAMOND, c, a), Cell(ACS_DIAMOND, c, a));
		break;
		case Board:
		set_border(Cell(ACS_BOARD, c, a), Cell(ACS_BOARD, c, a), Cell(ACS_BOARD, c, a), Cell(ACS_BOARD, c, a), Cell(ACS_BOARD, c, a), Cell(ACS_BOARD, c, a), Cell(ACS_BOARD, c, a), Cell(ACS_BOARD, c, a));
		break;
		case CheckBoard:
		set_border(Cell(ACS_CKBOARD, c, a), Cell(ACS_CKBOARD, c, a), Cell(ACS_CKBOARD, c, a), Cell(ACS_CKBOARD, c, a), Cell(ACS_CKBOARD, c, a), Cell(ACS_CKBOARD, c, a), Cell(ACS_CKBOARD, c, a), Cell(ACS_CKBOARD, c, a));
		break;
		case Arrow:
		set_border(Cell(ACS_RARROW, c, a), Cell(ACS_LARROW, c, a), Cell(ACS_DARROW, c, a), Cell(ACS_UARROW, c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a));
		break;
		default:
		break;
	}

}

void Window::fill(const Cell& cell){
	cchar_t c = cell;
	wbkgrnd(m_win, &c);
}

void Window::fill(ColorPair color, Attr attr){
	Cell cell;
	cell.color = color == ColorPair::Default ? get_color() : color;
	cell.attr = attr;
	fill(cell);
}

Cell Window::get_background(){
	cchar_t c;
	wgetbkgrnd(m_win, &c);
	return c;
}

void Window::set_background(const Cell& cell){
	cchar_t c = cell;
	wbkgrndset(m_win, &c);
}

void Window::set_background(ColorPair color, Attr attr){
	Cell cell;
	cell.color = color == ColorPair::Default ? get_color() : color;
	cell.attr = attr;
	set_background(cell);
} 

/*
void Window::copy(const Window&, const IntRect&, const Vector2i&, bool convert_attr){

}

void Window::write(const Vector2i& coord, std::wstring, ColorPair color, Attr attr){

}
*/

void Window::clear(){
	wclear(m_win);
} 

void Window::clear(const IntRect& zone){
	
	Cell back = get_background();

	for(int j = zone.y ; j < zone.height ; j++){

		for (int i = zone.x; i < zone.width; i++){
			set_cell(Vector2i(i, j), back);
		}
	}
}

void Window::display(){
	wnoutrefresh(m_win);
} 
