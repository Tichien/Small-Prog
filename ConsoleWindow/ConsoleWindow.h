#pragma once
#include "Window.h"
#include "Rect.h"

class ConsoleWindow : public Window
{
protected:

	Vector2i m_position;

public:
	//using Window::setSize;
	
	ConsoleWindow();
	ConsoleWindow(int x, int y, int w, int h);
	ConsoleWindow(const Vector2i& position, const Vector2i& size);

	virtual void setPosition(int x, int y);
	void setPosition(Vector2i position);
	Vector2i getPosition() const;

	virtual void display() override;
};