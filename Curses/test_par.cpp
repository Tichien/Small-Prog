#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Canvas.h"
#include "Particle.h"

using namespace std;

void clear(Canvas& canvas, ParticleSystem& particles){

	/* effacement des cellules */
	//canvas.clear();
	//
	for(list<Particle>::iterator it = particles.particles.begin() ; it != particles.particles.end() ; ++it){
		canvas.unset(it->position.rounded());
	}
	/*
	for(int i = 0 ; i < (int)particles.particles.size() ; i++){
	}
	*/
/*
	for(int i = 0 ; i < (int)particles.size() ; i++){
		particles[i].update();
		particles[i].display(canvas);
	}
	canvas.display();
	*/
}

/* si la fonction renvoie vrai alors il faut appliquer le mode. */
bool input_handler(int input, int& mode, int& mouseX, int& mouseY){
		if(input == KEY_MOUSE){
			MEVENT event;

			getmouse(&event);

			mouseX = event.x;
			mouseY = event.y;

			return true;
		}
		else if(input == 'r'){ //Repeller mode
			mode = 'r';
		}
		else if(input == 'a'){ //Attractor mode
			mode = 'a';
		}
		else if(input == 'p'){ //Particle mode
			mode = 'p';
		}

		return false;
}



int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int n = 100;
	float lifespan = 1000;
	Vector2f gravity(0, 0.02);
	Vector2f wind(0, 0);

	if(argc > 1)
		n = atoi(argv[1]);

	if(argc > 2)
		lifespan = atof(argv[2]);

	if(argc > 3)
		gravity.y = atof(argv[3]);

	if(argc > 4)
		wind.x = atof(argv[4]);

	if(argc > 5)
		wind.y = atof(argv[5]);


	float FRAME_RATE = 30.0;

	Term::init_curs();
	nodelay(stdscr, TRUE);
	//Term::scr.set_input_timeout(0);

	Canvas canvas;
	nodelay(canvas, TRUE);
	//canvas.set_input_timeout(1000.0 / 60.0);
	keypad(canvas, TRUE);
	
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

	canvas.set_attr(Attr::Bright);
	canvas.set_color(ColorPair::Default);

	vector<ParticleSystem> PS;

	PS.push_back(ParticleSystem(Vector2f(canvas.get_size()) / float(2)));
	//PS.push_back(ParticleSystem(Vector2f(canvas.get_size()) / float(1.5)));

	int input = 0;
	int mode = 'p';
	int nbframe = 0;

	float input_time = 0.0;
	float update_time = 0.0;
	float frame_time = 0.0;

	Vector2f att_pos(Vector2f(canvas.get_size()) / float(2));
	
	vector<Repeller> reps;
	vector<Attractor> atts;

	Repeller rep(att_pos);
	Attractor att(att_pos);

	int mouseX = 0, mouseY = 0;

	while(true){//Term::pop_input() != 'q') {
		
		nbframe++;

		float total_time = clock();

		for (int i = 0; i < n ; ++i){
			for(int j = 0 ; j < (int)PS.size() ; ++j){
				PS[j].add_particle(lifespan);
			}
		}

		for(int i = 0 ; i < (int)PS.size() ; ++i){
			PS[i].apply_force(gravity + wind);
			
			for(int k = 0 ; k < (int)reps.size() ; ++k)
				PS[i].apply_repeller(reps[k]);
			
			for(int k = 0 ; k < (int)atts.size() ; ++k)
				PS[i].apply_attractor(atts[k]);
		}

		float creation_time = (clock() - total_time) / (float)CLOCKS_PER_SEC;	
		
		float clear_time = clock();

		canvas.clear();
		//touchwin(canvas);

		clear_time = (clock() - clear_time) / (float)CLOCKS_PER_SEC;

		float run_time = clock();

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

		run_time = (clock() - run_time) / (float)CLOCKS_PER_SEC;
		
		float display_time = clock();

		canvas.display();

		display_time = (clock() - display_time) / (float)CLOCKS_PER_SEC;
		
		
		int i = 0;
		mvwprintw(canvas, i+0, 0, "Particles : %d/s, Creation : %f, Run : %f", n * PS.size(), creation_time, run_time);
		mvwprintw(canvas, i+1, 0, "Frame time : %f, Clear : %f, Display : %f, Update : %f", frame_time, clear_time, display_time, update_time);
		mvwprintw(canvas, i+2, 0, "Input time : %f, Mouse pos : %d %d   ", input_time, mouseX, mouseY);
		
		canvas.display();

		update_time = clock();

		Term::update();
		
		update_time = (clock() - update_time) / (float)CLOCKS_PER_SEC;

		input_time = clock();

		input = canvas.pop_input();

		if(input_handler(input, mode, mouseX, mouseY)){

			Vector2f origin(cell_to_pixel_pos(mouseX, mouseY));

			if(mode == 'r'){
				reps.push_back(Repeller(origin));
			}
			else if(mode == 'a'){
				atts.push_back(Attractor(origin));
			}
			else if(mode == 'p'){
				PS.push_back(ParticleSystem(origin));
			}
		}
		
		input_time = (clock() - input_time) / (float)CLOCKS_PER_SEC;

		frame_time = (clock() - total_time) / (float)CLOCKS_PER_SEC;
		
		//fflush(stdout);
		//Term::wait(1000.0 / FRAME_RATE);
	}
	
	canvas.display();
	Term::update();

	Term::pop_input();

	Term::end_curs();

	return 0;
}