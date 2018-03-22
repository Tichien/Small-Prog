#pragma once
#include "ConsoleScreen.h"

class Console
{
public:
	static Window Screen;

	static void startPowerMode();
	static void endPowerMode();

	static void saveState();
	static void loadState();

	static void update();
};