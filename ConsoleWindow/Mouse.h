#pragma once
#include "Vector2.h"
#include "ConsoleWindow.h"

class Mouse {

public:

	enum Button { Left, Right, Middle };
	enum Wheel { ScrollUp, ScrollDown };

	static int lastPressedInput;
	static bool aButtonIsPressed;

	static Vector2i getPosition();
	static Vector2i getPosition(ConsoleWindow& relativeTo);

	static bool isButtonPressed(Button button);
	static bool isButtonReleased(Button button);
	static bool isWheelScrolling(Wheel wheel);
};
