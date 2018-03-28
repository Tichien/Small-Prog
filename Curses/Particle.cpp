#include "Particle.h"

Particle::Particle() : position(), acceleration(), velocity(), lifespan() {}
Particle::Particle(const Vector2f& position, float lifespan) : position(position), acceleration(), velocity(), lifespan(lifespan) {}

void Particle::update() { 
	velocity += acceleration;
	position += velocity;
	lifespan--;
}

void Particle::display(Canvas& c) {
	c.set(round(position.x), round(position.y));
}

bool Particle::is_alive() {
	return lifespan > 0;
}