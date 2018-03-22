#include "ConsoleWindow.h"
#include "Console.h"

ConsoleWindow::ConsoleWindow() : Window() {}

ConsoleWindow::ConsoleWindow(int x, int y, int w, int h) :  m_position(x, y) {
	m_win = newpad(h, w);
	m_size = Vector2i(w, h);
}

ConsoleWindow::ConsoleWindow(const Vector2i& position, const Vector2i& size) : ConsoleWindow(position.x, position.y, size.x, size.y) {}

void ConsoleWindow::setPosition(int x, int y){
	m_position = Vector2i(x, y);
}

void ConsoleWindow::setPosition(Vector2i position){
	setPosition(position.x, position.y);
}

Vector2i ConsoleWindow::getPosition() const{
	return m_position;
}

void ConsoleWindow::display(){
	Rect intersec;
	Rect drawable(getPosition(), getSize());
	Rect screen(Vector2i::Zero, Console::Screen.getSize());

	if (drawable.intersects(screen, intersec) && drawable.height > 0 && drawable.width > 0) {
		int offsetX = 0, offsetY = 0;
		if (drawable.x < 0) { offsetX = -drawable.x; }
		if (drawable.y < 0) { offsetY = -drawable.y; }
		pnoutrefresh(m_win, offsetY, offsetX, intersec.y, intersec.x, intersec.y + (intersec.height - 1), intersec.x + (intersec.width - 1));
	}
}