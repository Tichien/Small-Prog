#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Canvas.h"

class Particle {

public:
  Vector2f position;
  Vector2f velocity;
  Vector2f acceleration;
  float lifespan;

  Particle();
  Particle(const Vector2f& position, float lifespan = 100);

  void update();
 
  void display(Canvas& c);

  bool is_alive();

};

#endif
