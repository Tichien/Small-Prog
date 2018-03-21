#include "unidraw.h"

wint_t braille_char_offset = 0x2800;

int pixel_map[4][2] = { {0x01, 0x08}, 
                        {0x02, 0x10},
                        {0x04, 0x20},
                        {0x40, 0x80} };

Canvas::Canvas(){
	int h = 0, w = 0;

	getmaxyx(stdscr, h, w);

	m_frame = newpad(h, w);
}
/*
Canvas::Canvas(int col, int row, int w, int h){
	m_frame = newpad(h, w);
}
*/
Canvas::~Canvas(){
	delwin(m_frame);
}

void Canvas::set(int x, int y){
	int col, row;

	pixel2cell(x, y, col, row);

	wint_t cell = getcell(col, row);

	if(!is_braille(cell))
		cell = braille_char_offset;

	cell |= pixel_map[y % 4][x % 2];

	setcell(col, row, cell);
}

void Canvas::unset(int x, int y){
	int col, row;

	pixel2cell(x, y, col, row);

	wint_t cell = getcell(col, row);

	if(!is_braille(cell))
		return;

	cell &= ~pixel_map[y % 4][x % 2];

	setcell(col, row, cell);
}

void Canvas::toggle(int x, int y){
	int col, row;

	pixel2cell(x, y, col, row);

	wint_t cell = getcell(col, row);

	if(is_braille(cell) && cell & pixel_map[y % 4][x % 2])
		unset(x, y);
	else
		set(x, y);
}

wint_t Canvas::getcell(int col, int row){
	wchar_t wc[2] = {0};
	mvwinnwstr(m_frame, row, col, wc, 1);
	return wc[0];
}

void Canvas::setcell(int col, int row, wint_t c){
	wchar_t wc[2] = {0}; wc[0] = c;
	mvwaddnwstr(m_frame, row, col, wc, 1);
}
/*
void Canvas::write(int col, int row, const char* text){
}
*/

void Canvas::clear(int col, int row, int w, int h){
	wclear(m_frame);
}

void Canvas::display(){
	int h, w;
	getmaxyx(stdscr, h, w);
	prefresh(m_frame, 0, 0, 0, 0, h, w);
}

bool Canvas::is_set(int x, int y){
	int col, row;
	pixel2cell(x, y, col, row);
	wint_t cell = getcell(col, row);
	return is_braille(cell) && cell & pixel_map[y % 4][x % 2];
}

void pixel2cell(int x, int y, int& col, int& row){
	col = x / 2;
	row = y / 4;
}

bool is_braille(wint_t cell){
	return cell >= 0x2800 && cell <= 0x28FF;
}
/*
void draw(const Canvas& c){

}

void drawLine(int x1, int y1, int x2, int y2){

}
*/