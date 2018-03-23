#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <clocale>
#include <cwchar>

extern "C"{
#include <ncursesw/curses.h>
}

#include "Rect.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS CANVAS

class Canvas {

public:
	WINDOW* m_frame;
 
public:
	Canvas();
	Canvas(int w, int h);
	virtual ~Canvas();

	void set(int x, int y);
	void set(const Vector2i& point);
	
	void unset(int x, int y);
	void unset(const Vector2i& point);
	
	void toggle(int x, int y);
	void toggle(const Vector2i& point);

	wint_t get_cell(int row, int col) const;
	wint_t get_cell(const Vector2i& cell_coord) const;

	void set_cell(int row, int col, wint_t c);
	void set_cell(const Vector2i& cell_coord, wint_t c);

	/* Renvoie les dimension du canvas en nombre de pixel (width, height) */
	Vector2i get_size() const;

	/* Renvoie les dimension du canvas en nombre de cellules (row, col) */
	Vector2i get_cells_size() const;

	void write(int x, int y, const std::string& text);
	void write(const Vector2i& position, const std::string& text);

	void clear(int col = 0, int row = 0, int w = 0, int h = 0);

	void display();
	void display(const Vector2i& position, const IntRect& offset);

	bool is_set(int x, int y);
};

/* Converti les coordonnées du pixel (x, y) en coordonnée de cellule (row, col) */
Vector2i pixel_to_cell_coord(int x, int y);
Vector2i pixel_to_cell_coord(const Vector2i& point);

/* Converti les coordonnées de la cellule (row, col) en coordonnée de pixel (x, y) */
Vector2i cell_to_pixel_coord(int row, int col);
Vector2i cell_to_pixel_coord(const Vector2i& cell_coord);

bool is_braille(wint_t cell);

void draw_line(Canvas& canvas, int x1, int y1, int x2, int y2);
void draw_line(Canvas& canvas, const Vector2i& p1, const Vector2i p2);

#endif
