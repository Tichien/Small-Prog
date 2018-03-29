#include "Particle.h"

Particle::Particle() : position(), velocity(), acceleration(), lifespan() {}
Particle::Particle(const Vector2f& position, float lifespan) : position(position), velocity(), acceleration(), lifespan(lifespan) {}
Particle::Particle(const Vector2f& pos, const Vector2f& v, const Vector2f& a) : position(pos), velocity(v), acceleration(a), lifespan(100) {} 

void Particle::update() { 
	velocity += acceleration;
	position += velocity;
	lifespan -= 1.0;
}

void Particle::display(Canvas& c) {
	c.set(round(position.x), round(position.y));
}

void Particle::run(Canvas& c) {
	update();
	display(c);
}

bool Particle::is_alive() {
	return lifespan > 0;
}

ParticleSystem::ParticleSystem() : particles() {}

ParticleSystem::ParticleSystem(int number, const Vector2f& position) : particles(number){
	for(int i = 0 ; i < number ; i++){
		particles[i] = Particle(position);
	}
}

void ParticleSystem::add(const Particle& p){
	particles.push_back(p);
}


void ParticleSystem::run(Canvas& c){
	for(int i = 0 ; i < (int)particles.size() ; i++){
		
		c.unset(round(particles[i].position.x), round(particles[i].position.y));
		
		if(particles[i].is_alive())
			particles[i].run(c);
		else
			particles.erase(particles.begin() + i);
	}
}