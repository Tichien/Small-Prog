extern "C"{
#include <curses.h>
}

#include "unidraw.h"

Canvas::Canvas(){
	int h = 0, w = 0;

	getmaxyx(stdscr, h, w);

	m_frame = newpad(h, w);
}

Canvas::Canvas(int col, int row, int w, int h){
	m_frame = newpad(h, w);
}

void Canvas::set(int x, int y){

}

void Canvas::unset(int x, int y){

}

void Canvas::toggle(int x, int y){

}


void Canvas::write(int col, int row, const char* text){

}

void Canvas::clear(int col, int row, int w, int h){

}


bool Canvas::is_set(int x, int y){

}

void pixel2cell(int x, int y, int& col, int& row){
	
}

void draw(const Canvas& c){

}

void drawLine(int x1, int y1, int x2, int y2){

}
