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
    
	Term::init_curs();

    int k = 400;
	Canvas canvas;//(radius * 2 + 1, radius * 2 + 1);
	/*
	for(int i = 0 ; i < canvas.get_size().x; i++){
		for(int j = 0 ; j < canvas.get_size().y ; j++){
			canvas.set(i, j);
		}
	}
	*/
	mvwprintw(stdscr, 0, 0, "Canvas.size = (%d, %d)", canvas.get_size().x, canvas.get_size().y);
	mvwprintw(stdscr, 1, 0, "Canvas.dimension = (%d, %d)", canvas.get_dimension().x, canvas.get_dimension().y);

	canvas.set_color(ColorPair::Red);
	canvas.set_attr(Attr::HalfBright);

	Vector2i p1(10, 20);
	Vector2i p2(135, 97);
	
	draw_polygon(canvas, center, sides, radius, rotation);

	//Turtle T(&canvas);

	//T.turn(45);
	//T.draw(1000);

	Vector2i printposition(0, 0);
	IntRect canvasoffset(0, 0, 10, 10);

	//canvas.fill(Cell('+'));
	int c = 0;

	canvas.display(Vector2i(0, 0));
	Term::update();

	//Term::pop_input();


	while((c = Term::pop_input()) != 'q'){
		handler(c, printposition, canvasoffset);
		canvas.display(printposition);
		Term::update();
	}

	Term::end_curs();
	
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