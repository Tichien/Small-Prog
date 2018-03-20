#ifndef _UNIDRAW_H_
#define _UNIDRAW_H_

int braille_start_char = 0x2800;

int pixel_map[4][2] = { {0x01, 0x08}, 
                        {0x02, 0x10},
                        {0x04, 0x20},
                        {0x40, 0x80} };


class Canvas {

	WINDOW* m_frame;

	Canvas();
	Canvas(int col, int row, int w, int h);

	void set(int x, int y);
	void unset(int x, int y);
	void toggle(int x, int y);

	void write(int col, int row, const char* text);
	void clear(int col, int row, int w, int h);

	bool is_set(int x, int y);
};

void pixel2cell(int x, int y, int& col, int& row);
void draw(const Canvas& c);
void drawLine(int x1, int y1, int x2, int y2);

#endif