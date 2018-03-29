#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <list>
#include "Canvas.h"

class Particle {

public:
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	float lifespan;

	Particle();
	Particle(const Vector2f& position, float lifespan = 100);
	Particle(const Vector2f& pos, const Vector2f& v, const Vector2f& a, float lifespan = 100);

	void update();

	void display(Canvas& c);

	void run(Canvas& c);

	bool is_alive();

};

class ParticleSystem {

public:
	std::list<Particle> particles;

	ParticleSystem();
	ParticleSystem(int number, const Vector2f& position);

	void add(const Particle& p);
	void run(Canvas& c);
};

#endif
