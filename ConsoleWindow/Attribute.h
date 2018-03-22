#pragma once

extern "C" {
#include "curses.h"
}

class Attribute
{
private:
	chtype m_attribute;

public:

	Attribute();
	Attribute(chtype);
	operator chtype() const;

	static const Attribute Normal;
	static const Attribute Standout;
	static const Attribute Underline;
	static const Attribute Reverse;
	static const Attribute Blink;
	static const Attribute HalfBright;
	static const Attribute Bold;
	static const Attribute Protected;
	static const Attribute Invisible;
	static const Attribute AltCharset;
	static const Attribute Default;
};