#ifndef _GNU_SOURCE
#define _GNU_SOURCE 
#endif

#include "unidraw.h"

////////////////////////////////////////////////// VARIABLES STATIQUES

const wint_t braille_char_offset = 0x2800;

const int pixel_map[4][2] = { 	{0x01, 0x08}, 
{0x02, 0x10},
{0x04, 0x20},
{0x40, 0x80} };

////////////////////////////////////////////////// CONSTRUCTEURS

Canvas::Canvas(){
	int h = 0, w = 0;

	getmaxyx(stdscr, h, w);

	m_frame = newpad(h, w);
}

Canvas::Canvas(int w, int h){
	//int col, row;
	/* converti le nombre de pixels en nombre de colonnes/lignes */
	//pixel2cell(w, h, col, row);
	if(!(w % 2 == 0))
		w+=2;
	if(!(h % 4 == 0))
		h+=4;
	
	m_frame = newpad(h / 4, w / 2);
} 

Canvas::~Canvas(){
	delwin(m_frame);
}

////////////////////////////////////////////////// METHODES

void Canvas::set(int x, int y){
	int col, row;

	pixel2cell(x, y, col, row);

	wint_t cell = get_cell(col, row);

	if(!is_braille(cell))
		cell = braille_char_offset;

	cell |= pixel_map[y % 4][x % 2];

	set_cell(col, row, cell);
}

void Canvas::unset(int x, int y){
	int col, row;

	pixel2cell(x, y, col, row);

	wint_t cell = get_cell(col, row);

	if(!is_braille(cell))
		return;

	cell &= ~pixel_map[y % 4][x % 2];

	set_cell(col, row, cell);
}

void Canvas::toggle(int x, int y){
	int col, row;

	pixel2cell(x, y, col, row);

	wint_t cell = get_cell(col, row);

	if(is_braille(cell) && cell & pixel_map[y % 4][x % 2])
		unset(x, y);
	else
		set(x, y);
}

wint_t Canvas::get_cell(int col, int row) const {
	wchar_t wc[2] = {0};
	mvwinnwstr(m_frame, row, col, wc, 1);
	return wc[0];
}

void Canvas::set_cell(int col, int row, wint_t c){
	wchar_t wc[2] = {0}; wc[0] = c;
	mvwaddnwstr(m_frame, row, col, wc, 1);
}

Vector2i Canvas::get_size() const {
	int h = 0, w = 0;
	getmaxyx(m_frame, h, w);
	return Vector2i(w * 2, h * 4);
}

void Canvas::write(int col, int row, const std::string& text){

	mvwprintw(m_frame, row, col, text.c_str());
}

void Canvas::clear(int col, int row, int w, int h){
	wclear(m_frame);
}

void Canvas::display(){
	int h, w;
	
	getmaxyx(stdscr, h, w);
	
	IntRect inter;
	IntRect screen(0, 0, w, h);
	IntRect canvas(Vector2i::zero, get_size());

	if(canvas.intersects(screen, inter))
		prefresh(m_frame, 0, 0, inter.y, inter.x, inter.y + (inter.height - 1), inter.x + (inter.width - 1));
}

void Canvas::display(const Vector2i& position, const IntRect& canvas_zone){
	int h, w;
	
	getmaxyx(stdscr, h, w);
	
	IntRect inter;
	IntRect screen(0, 0, w, h);

	if (canvas_zone.intersects(screen, inter) && canvas_zone.height > 0 && canvas_zone.width > 0) {
		int offsetX = position.x, offsetY = position.y;
		if (position.x < 0) { offsetX = -position.x; }
		if (position.y < 0) { offsetY = -position.y; }
		prefresh(m_frame, canvas_zone.y, canvas_zone.x, offsetY, offsetX, offsetY + inter.height, offsetX + inter.width);
	}
}

bool Canvas::is_set(int x, int y){
	int col, row;
	pixel2cell(x, y, col, row);
	wint_t cell = get_cell(col, row);
	return is_braille(cell) && cell & pixel_map[y % 4][x % 2];
}

void pixel2cell(int x, int y, int& col, int& row){
	col = x / 2;
	row = y / 4;
}

Vector2i pixel2cell(const Vector2i& point){
	return Vector2i(point.x / 2, point.y / 4);
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