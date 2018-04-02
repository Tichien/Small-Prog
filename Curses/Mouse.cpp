#include "Mouse.h"

bool Mouse::aButtonIsPressed = false;
int Mouse::lastPressedInput = -1;
Vector2i Mouse::position(-1, -1);

Vector2i Mouse::getPosition() {
	/*
	int x = -1, y = -1;
	
	MEVENT event;
	
	if (getmouse(&event) == OK) {
		x = event.x;
		y = event.y;
	}
	else
		printw("problem");
*/
	return Mouse::position;//Vector2i(x, y);
}

/*
Vector2i Mouse::getPosition(Window& relativeTo) {

	return Mouse::getPosition() - relativeTo.get_position();
}
*/

bool Mouse::isButtonPressed(Button button) {

	bool isPressed = false;

	if(Term::get_input() == KEY_MOUSE) {

		MEVENT event;

		if(getmouse(&event) == OK) {
			switch(button)
			{
				case Mouse::Left:
				isPressed = event.bstate == BUTTON1_PRESSED;
				break;
				case Mouse::Right:
				isPressed = event.bstate == BUTTON3_PRESSED;
				break;
				case Mouse::Middle:
				isPressed = event.bstate == BUTTON2_PRESSED;
				break;
				default:
				return false;
				break;
			}

			if(isPressed) {
				lastPressedInput = event.bstate;
				aButtonIsPressed = true;
			}

			Mouse::position = Vector2i(event.x, event.y);
			//ungetmouse(&event);
		}
	}
	/*
	else if(aButtonIsPressed) {
		switch(button)
		{
			case Mouse::Left:
			return lastPressedInput == BUTTON1_PRESSED;
			break;
			case Mouse::Right:
			return lastPressedInput == BUTTON3_PRESSED;
			break;
			case Mouse::Middle:
			return lastPressedInput == BUTTON2_PRESSED;
			break;
			default:
			return false;
			break;
		}
	}
*/
	//ungetch(KEY_MOUSE);

	return isPressed;
}

bool Mouse::isButtonReleased(Button button) {

	bool isReleased = false;

	if (Term::get_input() == KEY_MOUSE) {

		MEVENT event;

		if (getmouse(&event) == OK) {
			switch (button)
			{
				case Mouse::Left:
				isReleased = event.bstate == BUTTON1_RELEASED;
				break;
				case Mouse::Right:
				isReleased = event.bstate == BUTTON3_RELEASED;
				break;
				case Mouse::Middle:
				isReleased = event.bstate == BUTTON2_RELEASED;
				break;
				default:
				return false;
				break;
			}
			if (isReleased) {
				aButtonIsPressed = false;
			}
		}
	}
	return isReleased;
}

bool Mouse::isWheelScrolling(Wheel wheel) {

	if (Term::get_input() == KEY_MOUSE) {
		MEVENT event;
		if (getmouse(&event) == OK) {
			switch (wheel)
			{
				case Mouse::ScrollUp:
				return event.bstate == BUTTON4_PRESSED;
				break;
				case Mouse::ScrollDown:
				//return event.bstate == BUTTON5_PRESSED;
				break;
				default:
				return false;
				break;
			}
		}
	}
	return false;
}
