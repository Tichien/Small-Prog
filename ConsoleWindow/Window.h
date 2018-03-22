#pragma once
#include "Cellule.h"
#include "Vector2.h"

class Window
{
protected:
	WINDOW* m_win;

	Vector2i m_position;
	Vector2i m_size;

	Attribute m_attribute;
	ConsoleColor m_color;

	Cellule m_border[8];

	int m_input = -1;

	void setBorderArray(Cellule left, Cellule right, Cellule up, Cellule down, Cellule upLeft, Cellule upRight, Cellule downLeft, Cellule downRight);
	Window(WINDOW* win);

public:

	enum BorderType {
		Empty,
		Thin,
		Point,
		Dash,
		Block,
		Diamond,
		Board,
		CheckBoard,
		Arrow,
	};

	Window();
	virtual ~Window();

	void setScrollingEnabled(bool scrolling);
	void setEchoKeyEnabled(bool echoKey);
	void setInteractiveModeEnabled(bool interactive);
	void setSpecialKeySignalEnabled(bool specialKey);
	void setMouseSignalEnabled(bool mouse);
	void setCursorVisibility(int visibility);

	int read();
	int getInput();

	void scroll(int n);
	void setInputDelay(int delay);

	void copyText(const Window& win);

	virtual void setSize(int width, int height);
	virtual void setSize(Vector2i size);
	Vector2i getSize() const;

	void setCursorPosition(int x, int y);
	void setCursorPosition(const Vector2i& position);
	Vector2i getCursorPosition() const;

	void setCellule(int x, int y, const Cellule& c);
	Cellule getCellule(int x, int y) const;

	void setAttribute(const Attribute& attr);
	Attribute getAttribute() const;

	void setColor(const ConsoleColor& c);
	ConsoleColor getColor() const;

	void fill(const ConsoleColor& c, const Attribute& a);

	void write(const std::string& text, const ConsoleColor& c = ConsoleColor::Default, const Attribute& a = Attribute::Default, bool resetCursPos = false);
	void write(const std::string& text, int x, int y, const ConsoleColor& c = ConsoleColor::Default, const Attribute& a = Attribute::Default, bool resetCursPos = false);
	void write(const std::string& text, const Vector2i& position, const ConsoleColor& c = ConsoleColor::Default, const Attribute& a = Attribute::Default, bool resetCursPos = false);

	void setBorder(Cellule left, Cellule right, Cellule up, Cellule down, Cellule upLeft, Cellule upRight, Cellule downLeft, Cellule downRight);
	void setBorder(BorderType b, const ConsoleColor& color = ConsoleColor::Default, const Attribute& attribute = Attribute::Default);
	const Cellule* getBorder() const;

	void clear();
	virtual void display();
};