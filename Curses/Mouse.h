#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "Term.h"

class Mouse {

public:

	static Vector2i position;

	enum Button { Left, Right, Middle };
	enum Wheel { ScrollUp, ScrollDown };

	static int lastPressedInput;
	static bool aButtonIsPressed;

	static Vector2i getPosition();
	//static Vector2i getPosition(Window& relative_to);

	static bool isButtonPressed(Button button);
	static bool isButtonReleased(Button button);
	static bool isWheelScrolling(Wheel wheel);
};

#endif

