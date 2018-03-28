#ifndef _ATTR_H_
#define _ATTR_H_

extern "C"{
#include <ncursesw/curses.h>
}

class Attr
{
private:
	chtype m_attribute;

public:

	Attr();
	Attr(chtype);
	operator chtype() const;

	static const Attr Normal;
	static const Attr Standout;
	static const Attr Underline;
	static const Attr Reverse;
	static const Attr Blink;
	static const Attr HalfBright;
	static const Attr Bright;
	static const Attr Protected;
	static const Attr Invisible;
	static const Attr AltCharset;
	static const Attr Italic;

	//Ne font rien sur Windows
	/*
	static const Attr Horizontal;
	static const Attr Vertical;
	static const Attr Top;
	static const Attr Low;
	static const Attr Left;
	static const Attr Right;
	*/
};

#endif
