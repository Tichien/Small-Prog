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

	for(int i = 0; i < 20 ; i++){
		for(int j = 0 ; j < 20 ; j++){
			if(i == j)
				canvas.set(i, j);
		}
	}

	canvas.display();
	

	getch();

	endwin();
	return 0;
}