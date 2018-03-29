#include "Particle.h"

Particle::Particle() : position(), velocity(), acceleration(), lifespan() {}
Particle::Particle(const Vector2f& position, float lifespan) : position(position), velocity(), acceleration(), lifespan(lifespan) {}
Particle::Particle(const Vector2f& pos, const Vector2f& v, const Vector2f& a, float lifespan) : position(pos), velocity(v), acceleration(a), lifespan(lifespan) {} 

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
	for(int i = 0 ; i < (int)particles.size() ; i++){
		particles.push_back(Particle(position));
	}
}

void ParticleSystem::add(const Particle& p){
	particles.push_back(p);
}


void ParticleSystem::run(Canvas& c){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		
		//c.unset(round(it->position.x), round(it->position.y));

		if(it->is_alive())
			it->run(c);
		else
			it = particles.erase(it); //met a jour l'iterateur pour pointer vers l'iterateur suivant
	}
}