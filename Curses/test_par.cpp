#include <iostream>
#include <vector>
#include <cstdlib>
#include "Canvas.h"
#include "Particle.h"

using namespace std;

void run(Canvas& canvas, vector<Particle>& particles){
	canvas.clear();
	for(int i = 0 ; i < particles.size() ; i++){
		particles[i].update();
		particles[i].display(canvas);
	}
	canvas.display();
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));


	int n = 10000;
	int spd = 500;
	int gravity = 5;

	if(argc > 1)
		n = atoi(argv[1]);

	if(argc > 2)
		spd = atoi(argv[2]);

	if(argc > 3)
		gravity = atoi(argv[3]);

	Term::init_curs();
	Term::scr.set_input_timeout(1000 / 60);

	Canvas canvas;

	canvas.set_attr(Attr::Bright);
	canvas.set_color(ColorPair::Default);

	vector<Particle> particles(n);

	for(int i = 0 ; i < n ; i++){
		particles[i].position = Vector2f(canvas.get_size()) / float(2);
		particles[i].acceleration = Vector2f(0, gravity / 100.0);
		float x = ((float)(rand() % (spd + 1)) - (spd / 2)) / 10.0;
		float y = ((float)(rand() % (spd + 1)) - (spd / 2)) / 10.0;
		particles[i].velocity = Vector2f(x, y);
	}
	int ch = 0;
	while(Term::pop_input() != 'q') {
		run(canvas, particles);
		Term::update();
	}
	
	Term::update();

	Term::pop_input();

	Term::end_curs();

	return 0;
}