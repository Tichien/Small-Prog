#ifndef _TURTLE_H_
#define _TURTLE_H_

#include "Canvas.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS CANVAS

class Turtle
{
private:
	Canvas* m_canvas;
	Vector2f position;
	float rotation;
	bool write;

	bool allocated;

public:
	Turtle();
	Turtle(Canvas* canvas);
	~Turtle();

	void set_position(float x, float y);
	void set_position(const Vector2f& position);

	void draw(float distance);

	void move(float distance);

	void turn(float angle);
};

float to_radians(float);

void draw_polygon(Canvas& canvas, Vector2f center, int sides, float radius, float rotation);

#endif
