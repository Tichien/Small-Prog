#include "Clock.h"
#include <string>

Clock::Clock() : m_startTime(0) {
	m_startTime = clock();
}

void Clock::restart() {
	m_startTime = clock();
}

float Clock::getElapsedTime() {
	return (float) (clock() - m_startTime) / CLOCKS_PER_SEC;
}

std::string Clock::toString(){
	return std::to_string(getElapsedTime());
}
