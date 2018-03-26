#include <cstdlib>
#include <cstdio>

#include "Turtle.h"

using namespace std;

void handler(int ch, Vector2i& position, IntRect& offset);

int main(int argc, char** argv)
{

	int sides = 3;
	float radius = 50;
	float rotation = 0;

	if(argc > 1)
		sides = atoi(argv[1]);

	if(argc > 2)
		radius = atof(argv[2]);

	if(argc > 3)
		rotation = atof(argv[3]);

	Vector2f center(radius, radius);
    
    setlocale(LC_ALL, "");

    initscr();
    start_color();
        //cbreak();
    noecho();
    keypad(stdscr, TRUE);

    refresh();

    //resizeterm(200, 200);

    //init_pair(1, COL, COLOR_RED);

    int k = 800;
	Canvas canvas(k, k);
	
	wattron(canvas.m_frame, COLOR_PAIR(1));
	wattroff(canvas.m_frame, COLOR_PAIR(1));

	int imax = canvas.get_size().x;
	int jmax = canvas.get_size().y;

	Vector2i p1(10, 20);
	Vector2i p2(135, 97);
	
	
	for(int i = 0; i < imax ; i++){
		for(int j = 0 ; j < jmax ; j++){
			//if(i == j)
				//canvas.set(i, j);
		}
	}

	//draw_line(canvas, p1, p2);

	//draw_polygon(&canvas, Vector2f(100, 50), 5, nbc);
	//draw_polygon(canvas, Vector2f(20, 20), 0, nbc, distance);
	draw_polygon(canvas, center, sides, radius, rotation);


	Turtle T(&canvas);

	T.turn(45);
	T.draw(1000);


	Vector2i printposition(0, 0);
	IntRect canvasoffset(0, 0, 10, 10);

	//refresh(); 
	canvas.display();
	
	int c = 0;

	int h, w;
	
	getmaxyx(stdscr, h, w);

	while((c = getch()) != 'q'){
		clear();
		refresh();
		//wscrl(stdscr, 1);
		handler(c, printposition, canvasoffset);
		canvas.display(printposition, canvasoffset);
		//mvprintw(LINES-3, 0, "printposition : {%d, %d}", printposition.x, printposition.y);
		//mvprintw(LINES-2, 0, "canvasoffset : {%d, %d, %d, %d}", canvasoffset.x, canvasoffset.y, canvasoffset.width, canvasoffset.height);
		//mvprintw(h-1, 0, "Term size : {%d, %d}", h, w);
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