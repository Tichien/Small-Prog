#include "Window.h"

Window::Window() : m_win(NULL) { }

Window::Window(WINDOW* win) {
	m_win = win;
	int x = 0, y = 0;
	getmaxyx(win, y, x);
	setSize(x, y);
}

Window::~Window() {
	delwin(m_win);
}

void Window::setScrollingEnabled(bool scrolling){
	scrolling ? scrollok(m_win, true) : scrollok(m_win, false);
}

void Window::setEchoKeyEnabled(bool echoKey){
	echoKey ? echo() : noecho();
}

void Window::setInteractiveModeEnabled(bool interactive){
	interactive ? cbreak() : nocbreak();
}

void Window::setSpecialKeySignalEnabled(bool specialKey){
	specialKey ? keypad(m_win, true) : keypad(m_win, false);
}

void Window::setMouseSignalEnabled(bool mouse){
	mouse ? mousemask(ALL_MOUSE_EVENTS, NULL) : mousemask(0, NULL) ;
}

void Window::setCursorVisibility(int visibility){
	curs_set(visibility);
}

int Window::read(){
	m_input = wgetch(m_win);
	return m_input;
}

int Window::getInput(){
	return m_input;
}

void Window::scroll(int n){
	wscrl(m_win, n);
}

void Window::setInputDelay(int delay){
	wtimeout(m_win, delay);
}

void Window::copyText(const Window& win){
	chtype* str = new chtype[win.getSize().x * win.getSize().y];
	int k = 0;
	for (int j = 0; j < win.getSize().y; j++) {
		for (int i = 0; i < win.getSize().x; i++) {
			str[k] = win.getCellule(j, i);
			k++;
			if (k >= getSize().x * getSize().y) { break; }
		}
	}
	setCursorPosition(0, 0);
	for (int i = 0; i < k; i++) {
		waddch(m_win, str[i]);
	}
	delete[] str;
}

void Window::setSize(int width, int height){
	if(width >= 0 && height >= 0){
		m_size = Vector2i(width, height);

		WINDOW* win = newpad(height, width);

		wbkgd(win, m_color | m_attribute);

		overwrite(m_win, win);

		wresize(m_win, height, width);

		overwrite(win, m_win);

		delwin(win);
	}
}

void Window::setSize(Vector2i size){
	setSize(size.x, size.y);
}

Vector2i Window::getSize() const{
	return m_size;
}

void Window::setCursorPosition(int x, int y){
	wmove(m_win, y, x);
}

void Window::setCursorPosition(const Vector2i& position){
	setCursorPosition(position.x, position.y);
}

Vector2i Window::getCursorPosition() const{
	int x = 0, y = 0;
	getyx(m_win, y, x);
	return Vector2i(x, y);
}

Cellule Window::getCellule(int x, int y) const{
	return Cellule(mvwinch(m_win, y, x));
}

void Window::setCellule(int x, int y, const Cellule& c){
	mvwaddch(m_win, y, x, c);
}

void Window::setAttribute(const Attribute& attr){
	m_attribute = attr;
	wattrset(m_win, m_color | m_attribute);
} 

Attribute Window::getAttribute() const{
	return m_attribute;
}

void Window::setColor(const ConsoleColor& c){
	m_color = c;
	wattrset(m_win, m_color | m_attribute);
}

ConsoleColor Window::getColor() const{
	return m_color;
}

void Window::fill(const ConsoleColor &c, const Attribute &a){
	m_color = c;
	m_attribute = a;
	wbkgd(m_win, m_color | m_attribute);
}

void Window::write(const std::string& text, const ConsoleColor& c, const Attribute& a, bool resetCursPos){

	Attribute attr = m_attribute;
	ConsoleColor col = m_color;
	Vector2i cursPos = getCursorPosition();

	if(c != ConsoleColor::Default) { col = c; }
	if(a != Attribute::Default) { attr = a; }
	
	wattron(m_win, col | attr);
	wprintw(m_win, text.c_str());
	wattroff(m_win, col | attr);

	if(resetCursPos) {setCursorPosition(cursPos);}
}

void Window::write(const std::string& text, int x, int y, const ConsoleColor& c, const Attribute& a, bool resetCursPos){
	Attribute attr = m_attribute;
	ConsoleColor col = m_color;
	Vector2i cursPos = getCursorPosition();

	if(c != ConsoleColor::Default) { col = c; }
	if(a != Attribute::Default) { attr = a; }
	
	wattron(m_win, col | attr);
	mvwprintw(m_win, y, x, text.c_str());
	wattroff(m_win, col | attr);

	if(resetCursPos) {setCursorPosition(cursPos);}
}

void Window::write(const std::string& text, const Vector2i& position, const ConsoleColor& c, const Attribute& a, bool resetCursPos){
	write(text, position, c, a, resetCursPos);
}

void Window::setBorderArray(Cellule left, Cellule right, Cellule up, Cellule down, Cellule upLeft, Cellule upRight, Cellule downLeft, Cellule downRight){
	m_border[0] = left; m_border[1] = right; m_border[2] = up; m_border[3] = down;
	m_border[4] = upLeft; m_border[5] = upRight; m_border[6] = downLeft; m_border[7] = downRight;
}


void Window::setBorder(Cellule left, Cellule right, Cellule up, Cellule down, Cellule upLeft, Cellule upRight, Cellule downLeft, Cellule downRight){
	setBorderArray(left, right, up, down, upLeft, upRight, downLeft, downRight);
	wborder(m_win, left, right, up, down, upLeft, upRight, downLeft, downRight);
}

void Window::setBorder(BorderType b, const ConsoleColor& color, const Attribute& attribute){
	Attribute a = m_attribute;
	ConsoleColor c = m_color;

	if(color != ConsoleColor::Default) { c = color; }
	if(attribute != Attribute::Default) { a = attribute; }

	switch (b)
	{
		case Empty:
		setBorder({' ', c, a}, {' ', c, a}, {' ', c, a}, {' ', c, a}, {' ', c, a}, {' ', c, a}, {' ', c, a}, {' ', c, a});
		break;
		case Thin:
		setBorder({ACS_VLINE, c, a}, {ACS_VLINE, c, a}, {ACS_HLINE, c, a}, {ACS_HLINE, c, a}, {ACS_ULCORNER, c, a}, {ACS_URCORNER, c, a}, {ACS_LLCORNER, c, a}, {ACS_LRCORNER, c, a});
		break;
		case Point:
		setBorder({ACS_BULLET, c, a}, {ACS_BULLET, c, a}, {ACS_BULLET, c, a}, {ACS_BULLET, c, a}, {ACS_BULLET, c, a}, {ACS_BULLET, c, a}, {ACS_BULLET, c, a}, {ACS_BULLET, c, a});
		break;
		case Dash: 
		setBorder({'|', c, a}, {'|', c, a}, {'-', c, a}, {'-', c, a}, {'+', c, a}, {'+', c, a}, {'+', c, a}, {'+', c, a});
		break;
		case Block:
		setBorder({ACS_BLOCK, c, a}, {ACS_BLOCK, c, a}, {ACS_BLOCK, c, a}, {ACS_BLOCK, c, a}, {ACS_BLOCK, c, a}, {ACS_BLOCK, c, a}, {ACS_BLOCK, c, a}, {ACS_BLOCK, c, a});
		break;
		case Diamond:
		setBorder({ACS_DIAMOND, c, a}, {ACS_DIAMOND, c, a}, {ACS_DIAMOND, c, a}, {ACS_DIAMOND, c, a}, {ACS_DIAMOND, c, a}, {ACS_DIAMOND, c, a}, {ACS_DIAMOND, c, a}, {ACS_DIAMOND, c, a});
		break;
		case Board:
		setBorder({ACS_BOARD, c, a}, {ACS_BOARD, c, a}, {ACS_BOARD, c, a}, {ACS_BOARD, c, a}, {ACS_BOARD, c, a}, {ACS_BOARD, c, a}, {ACS_BOARD, c, a}, {ACS_BOARD, c, a});
		break;
		case CheckBoard:
		setBorder({ACS_CKBOARD, c, a}, {ACS_CKBOARD, c, a}, {ACS_CKBOARD, c, a}, {ACS_CKBOARD, c, a}, {ACS_CKBOARD, c, a}, {ACS_CKBOARD, c, a}, {ACS_CKBOARD, c, a}, {ACS_CKBOARD, c, a});
		break;
		case Arrow:
		setBorder({ACS_RARROW, c, a}, {ACS_LARROW, c, a}, {ACS_DARROW, c, a}, {ACS_UARROW, c, a}, {' ', c, a}, {' ', c, a}, {' ', c, a}, {' ', c, a});
		break;
		default:
		break;
	}
}

const Cellule* Window::getBorder() const {
	return m_border;
}

void Window::clear() {
	werase(m_win);
	display();
}

void Window::display() {
	wnoutrefresh(m_win);
}