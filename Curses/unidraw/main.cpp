#include <cstdlib>
#include <cstdio>

#include "unidraw.h"

using namespace std;

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

	mvprintw(LINES-1, 0, "Canvas size : {%d, %d}", canvas.get_size().x, canvas.get_size().y);
	canvas.write(0,3, "0123456789012345678901234567890123456789");
	wattroff(canvas.m_frame, COLOR_PAIR(1));

	canvas.display(Vector2i(0, 0), IntRect(0, 0, 40, 40));
	
	int c = 0;

	while((c = getch()) != 'q'){
		canvas.display();
	}

	endwin();
	return 0;
}