#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Term.h"
#include "Canvas.h"
#include "Particle.h"

using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int n = 100;
	float lifetime = 1000;
	Vector2f gravity(0, 0.02);
	Vector2f wind(0, 0);

	if(argc > 1)
		n = atoi(argv[1]);

	if(argc > 2)
		lifetime = atof(argv[2]);

	if(argc > 3)
		gravity.y = atof(argv[3]);

	if(argc > 4)
		wind.x = atof(argv[4]);

	if(argc > 5)
		wind.y = atof(argv[5]);


	float FRAME_RATE = 60.0;

	Term::init_curs();

	timeout(1000.0 / FRAME_RATE);

	Canvas canvas;
	nodelay(canvas, TRUE);
	//canvas.set_input_timeout(1000.0 / 60.0);
	keypad(canvas, TRUE);
	mouseinterval(0);
	
	canvas.set_attr(Attr::Bright);
	canvas.set_color(ColorPair::Default);

	ParticleSystem PS(lifetime, IntRect(0, 0, 0, 0), 0.91);
	//PS.add_particles(n, Vector2f(canvas.get_size()) / float(2.0));
	PS.add_particles(n, IntRect(Vector2i::zero, canvas.get_size()));

	//vector<ParticleSystem> PS;

	//PS.push_back(ParticleSystem(10000));
	//PS.push_back(ParticleSystem(Vector2f(canvas.get_size()) / float(1.5)));
 
	int nbframe = 0;

	float input_time = 0.0;
	float update_time = 0.0;
	float frame_time = 0.0;

	Vector2f att_pos(Vector2f(canvas.get_size()) / float(2));
	
	vector<Repeller> reps;
	vector<Attractor> atts;

	Repeller rep(att_pos);
	Attractor att(att_pos);

	while(!Keyboard::is_pressed(Keyboard::Escape)){//Term::pop_input() != 'q') {
		
		nbframe++;

		Term::read_input();

		float total_time = clock();

		float calc_time = clock();

		PS.apply_force(gravity + wind);

		for(int k = 0 ; k < (int)reps.size() ; ++k)
			PS.apply_repeller(reps[k]);
		
		for(int k = 0 ; k < (int)atts.size() ; ++k)
			PS.apply_attractor(atts[k]);

		/*
		for(int i = 0 ; i < (int)PS.size() ; ++i){

			nb_particles += PS[i].particles.size();

			PS[i].apply_force(gravity + wind);
			
			for(int k = 0 ; k < (int)reps.size() ; ++k){
				nb_repellers++;
				PS[i].apply_repeller(reps[k]);
			}
			
			for(int k = 0 ; k < (int)atts.size() ; ++k){
				nb_attractors++;
				PS[i].apply_attractor(atts[k]);
			}
		}
		*/	

		calc_time = (clock() - calc_time) / (float)CLOCKS_PER_SEC;

		float clear_time = clock();

		canvas.clear();

		clear_time = (clock() - clear_time) / (float)CLOCKS_PER_SEC;

		float run_time = clock();

		PS.run(canvas);
		/*

		for(int i = 0 ; i < (int)PS.size() ; ++i){

			if(i == 0)
				canvas.set_color(ColorPair::Green);
			else if(i == 1)
				canvas.set_color(ColorPair::Red);
			else
				canvas.set_color(ColorPair::Default);

			PS[i].run(canvas);
		}
		
		canvas.set_color(ColorPair::Default);
		*/
	
		run_time = (clock() - run_time) / (float)CLOCKS_PER_SEC;
		
		float display_time = clock();

		canvas.display();

		display_time = (clock() - display_time) / (float)CLOCKS_PER_SEC;
		
		mvwprintw(canvas, 0, 0, "Particles : %d, Attractors : %d, Repellers : %d", PS.particles.size(), atts.size(), reps.size());
		mvwprintw(canvas, 1, 0, "Calculation : %f, Runtime : %f", calc_time, run_time);
		mvwprintw(canvas, 2, 0, "Frame time : %f, Clear : %f, Display : %f, Update : %f", frame_time, clear_time, display_time, update_time);
		mvwprintw(canvas, 3, 0, "Input time : %f, Mouse pos : %d %d   ", input_time, Mouse::get_pos().x, Mouse::get_pos().y);
		
		canvas.display();

		update_time = clock();

		Term::update();
		
		update_time = (clock() - update_time) / (float)CLOCKS_PER_SEC;

		input_time = clock();

		Vector2f origin(cell_to_pixel_pos(Mouse::get_pos()));

		if(Mouse::is_pressed(Mouse::Left))
			PS.apply_repeller(Repeller(origin));
		else if(Mouse::is_pressed(Mouse::Right))
			PS.apply_attractor(Attractor(origin));
		//else if(Mouse::is_released(Mouse::Middle))
			//PS.push_back(ParticleSystem(origin));
		
		input_time = (clock() - input_time) / (float)CLOCKS_PER_SEC;

		frame_time = (clock() - total_time) / (float)CLOCKS_PER_SEC;
	}
	
	canvas.display();
	Term::update();

	Term::pop_input();

	Term::end_curs();

	return 0;
}