#include "Particle.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PARTICLE

Particle::Particle() : position(), velocity(random(-1, 1), random(-1, -1)), acceleration(), lifespan(), mass(1) {}

Particle::Particle(const Vector2f& position, float lifespan) : position(position), velocity(random(-1, 1), random(-1, -1)), acceleration(), lifespan(lifespan), mass(1){}

Particle::Particle(const Vector2f& pos, const Vector2f& v, float lifespan) : position(pos), velocity(v), acceleration(), lifespan(lifespan), mass(1) {} 

void Particle::apply_force(const Vector2f& force){
	acceleration += (force / mass);
}

void Particle::update() { 
	velocity += acceleration;
	position += velocity;
	acceleration = Vector2f::zero;
	lifespan -= 1.0;
}

void Particle::display(Canvas& c) {
		
	c.set(position.rounded());
	//c.toggle(round(position.x), round(position.y));
}

void Particle::run(Canvas& c) {
	update();
	display(c);
}

bool Particle::is_alive() {
	return lifespan > 0;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ATTRACTOR

Attractor::Attractor() : position(), strength(100), mass(1) {}

Attractor::Attractor(const Vector2f& position) : position(position), strength(100), mass(1) {}

Vector2f Attractor::attract(const Particle& p) const {

	Vector2f dir = position - p.position;
	
	//constrain dist pour ne pas perdre le controle des particules
	float dist = dir.length();
	dist = constrain(dist, 5, 50);

	dir.normalize();

	float force = (strength * mass * p.mass) / (dist * dist);
	
	return dir * force;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ REPELLER

Repeller::Repeller() : position(), strength(100), mass(1) {}

Repeller::Repeller(const Vector2f& position) : position(position), strength(100), mass(1) {}

Vector2f Repeller::repel(const Particle& p) const {

	Vector2f dir = position - p.position;
	
	//constrain dist pour ne pas perdre le controle des particules
	float dist = dir.length();
	dist = constrain(dist, 5, 50);

	dir.normalize();

	float force = (strength * mass * p.mass) / (dist * dist); 

	return -dir * force;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PARTICLESYSTEM

ParticleSystem::ParticleSystem() : particles(), origin() {}

ParticleSystem::ParticleSystem(const Vector2f& origin) : particles(), origin(origin) {}
 
void ParticleSystem::apply_force(const Vector2f& force){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		it->apply_force(force);
	}
}

void ParticleSystem::apply_repeller(const Repeller& rep){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		Vector2f force = rep.repel(*it);
		it->apply_force(force);
	}
}

void ParticleSystem::apply_attractor(const Attractor& att){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		Vector2f force = att.attract(*it);
		it->apply_force(force);
	}
}

void ParticleSystem::add_particle(float lifespan){
	add_particle(Particle(origin, lifespan));
}

void ParticleSystem::add_particle(const Particle& p){ 
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

float random(int start, int end, int precision){

	int longueur = abs(abs(end) - start);

	int randlong = (rand() % ((longueur * precision) + 1));

	return (float) start + ((float) randlong / (float) precision);
}

float constrain(float f, float start, float end){
	return f < start ? start : f > end ? end : f;  
}