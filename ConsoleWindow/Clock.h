#pragma once
#include <iostream>
#include <ctime>

class Clock
{
private:
	clock_t m_startTime;
public:
	Clock();
	void restart();
	float getElapsedTime();
	std::string toString();
};