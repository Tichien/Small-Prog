#include <cstdlib>
#include <cstdio>
#include <locale.h>

#include "unidraw.h"

int main()
{

    setlocale(LC_ALL, "");

    initscr();
    start_color();
        //cbreak();
    noecho();
    keypad(stdscr, TRUE);

    refresh();

	Canvas canvas;

	int imax = 200;
	int jmax = 200;

	for(int i = 0; i < imax ; i++){
		for(int j = 0 ; j < jmax ; j++){
			if(i == j){
				canvas.set(i, j);
				canvas.set(imax-1, jmax-1 -j);
			}
		}
	}

	canvas.write(10, 6, "TEXT");

	canvas.display();
	

	getch();

	endwin();
	return 0;
}