#include <iostream>
#include <vector>
#include <cstdlib>
#include "Canvas.h"
#include "Particle.h"

using namespace std;

void run(Canvas& canvas, vector<Particle>& particles){

	/* effacement des cellules */
	//canvas.clear();
	
	for(int i = 0 ; i < (int)particles.size() ; i++){
		canvas.unset(round(particles[i].position.x), round(particles[i].position.y));
	}
	

	for(int i = 0 ; i < (int)particles.size() ; i++){
		particles[i].update();
		particles[i].display(canvas);
	}
	canvas.display();
}

float random(int start, int end, int precision = 100000){

	int longueur = abs(abs(end) - start);

	int randlong = (rand() % ((longueur * precision) + 1));

	return (float) start + ((float) randlong / (float) precision);
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int n = 10000;
	int spd = 10;
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

	ParticleSystem particles;
	ParticleSystem particles2;

	/*
	vector<Particle> particles(n);

	for(int i = 0 ; i < n ; i++){
		particles[i].position = Vector2f(canvas.get_size()) / float(2);
		particles[i].acceleration = Vector2f(0, gravity / 100.0);
		particles[i].velocity = Vector2f(random(-spd, spd), random(-spd, spd));
	}
	*/
	int ch = 0;
	while(true){//Term::pop_input() != 'q') {
		//clear();
		
		for (int i = 0; i < (rand() % 10) ; ++i){
			Particle p(Vector2f(canvas.get_size()) / float(4), Vector2f(random(-1, 1), random(-2, 0)), Vector2f(0, (float)gravity / 100));
			Particle p2(Vector2f(canvas.get_size()) / float(1.5), Vector2f(random(-1, 1), random(-2, 0)), Vector2f(0, (float)gravity / 100));
			particles.add(p);
			particles2.add(p2);
		}
		mvprintw(0, 0, "Particles : %d", particles.particles.size() + particles.particles.size());
		
		particles.run(canvas);
		particles2.run(canvas);

		
		canvas.display();
		Term::update();
	}
	
	Term::update();

	Term::pop_input();

	Term::end_curs();

	return 0;
}