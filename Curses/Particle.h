#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <list>
#include <cstdlib>
#include "Canvas.h"

class Particle {

public:
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	float lifespan;
	float mass;

	Particle();
	Particle(const Vector2f& position, float lifespan = 100);
	Particle(const Vector2f& pos, const Vector2f& v, float lifespan = 100);

	void apply_force(const Vector2f& force);

	void update();

	void display(Canvas& c);

	void run(Canvas& c);

	bool is_alive();

};

class Attractor {

public:
	// Gravitational Constant
	Vector2f position;
	float strength;
	float mass;

	Attractor();
	Attractor(const Vector2f& position);

	Vector2f attract(const Particle& p) const;
};

class Repeller {

public:
	// Gravitational Constant
	
	Vector2f position;
	float strength; 
	float mass;
	Repeller();
	Repeller(const Vector2f& position);

	Vector2f repel(const Particle& p) const;
};

class ParticleSystem {

public:
	std::list<Particle> particles;
	Vector2f origin;

	ParticleSystem();
	ParticleSystem(const Vector2f& origin);

	void apply_force(const Vector2f& force);
	
	void apply_repeller(const Repeller& rep);
	
	void apply_attractor(const Attractor& att);
	
	void add_particle(float lifespan = 1000);
	void add_particle(const Particle& p);
	
	void run(Canvas& c);
};

float random(int start, int end, int precision = 100000);
float constrain(float f, float start, float end);

#endif
