#include "Attribute.h"

Attribute::Attribute() : m_attribute(A_NORMAL) {
}

Attribute::Attribute(chtype c) : m_attribute(c & A_ATTRIBUTES) {}

Attribute::operator chtype() const {
	return m_attribute;
}

const Attribute Attribute::Normal(A_NORMAL);
const Attribute Attribute::Standout(A_STANDOUT);
const Attribute Attribute::Underline(A_UNDERLINE);
const Attribute Attribute::Reverse(A_REVERSE);
const Attribute Attribute::Blink(A_BLINK);
const Attribute Attribute::HalfBright(A_DIM);
const Attribute Attribute::Bold(A_BOLD);
const Attribute Attribute::Protected(A_PROTECT);
const Attribute Attribute::Invisible(A_INVIS);
const Attribute Attribute::AltCharset(A_ALTCHARSET);
const Attribute Attribute::Default(A_NORMAL);

