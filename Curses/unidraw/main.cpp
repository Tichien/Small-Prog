#include <cstdlib>
#include <cstdio>

#include "unidraw.h"

using namespace std;

void handler(int ch, Vector2i& position, IntRect& offset);

int main()
{

    setlocale(LC_ALL, "");

    initscr();
    start_color();
        //cbreak();
    noecho();
    keypad(stdscr, TRUE);

    refresh();

    init_pair(1, COLOR_GREEN, COLOR_RED);

    int k = 400;
	Canvas canvas(k, k);
	wattron(canvas.m_frame, COLOR_PAIR(1));

	int imax = canvas.get_size().x;
	int jmax = canvas.get_size().y;

	for(int i = 0; i < imax ; i++){
		for(int j = 0 ; j < jmax ; j++){
			canvas.set(i, j);
		}
	}

	canvas.write(0,2, "0         1         2         3         ");
	canvas.write(0,3, "0123456789012345678901234567890123456789");
	wattroff(canvas.m_frame, COLOR_PAIR(1));

	Vector2i printposition(0, 0);
	IntRect canvasoffset(0, 0, 10, 10);

	canvas.display();
	
	int c = 0;

	int h, w;
	
	getmaxyx(stdscr, h, w);

	while((c = getch()) != 'q'){
		clear();
		refresh();
		handler(c, printposition, canvasoffset);
		canvas.display(printposition, canvasoffset);
		mvprintw(LINES-3, 0, "printposition : {%d, %d}", printposition.x, printposition.y);
		mvprintw(LINES-2, 0, "canvasoffset : {%d, %d, %d, %d}", canvasoffset.x, canvasoffset.y, canvasoffset.width, canvasoffset.height);
		mvprintw(h-1, 0, "Term size : {%d, %d}", h, w);
	}

	endwin();
	return 0;
}

void handler(int ch, Vector2i& position, IntRect& offset){

	if(ch == KEY_UP){
		position += Vector2i::up;
	}
	else if(ch == KEY_DOWN){
		position += Vector2i::down;
	}	
	else if(ch == KEY_LEFT){
		position += Vector2i::left;
	}	
	else if(ch == KEY_RIGHT){
		position += Vector2i::right;
	}	
	else if(ch == 'e'){
		offset.x += Vector2i::up.x;
		offset.y += Vector2i::up.y;	
	}
	else if(ch == 'd'){
		offset.x += Vector2i::down.x;
		offset.y += Vector2i::down.y;	
	}	
	else if(ch == 's'){
		offset.x += Vector2i::left.x;
		offset.y += Vector2i::left.y;	
	}	
	else if(ch == 'f'){
		offset.x += Vector2i::right.x;
		offset.y += Vector2i::right.y;
	}	
}