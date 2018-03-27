#ifndef _CELL_H_
#define _CELL_H_

/*
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED // pour utilisé les fonction wide character et cchar_t
#endif
*/
#include <cwchar>
#include "Color.h"
#include "Attr.h"

//la conversion en cchar_t pourrais etre meilleur je pense qu'il y a des characters unicode qui ne sont pas supporté
//mais pour l'instant ca marche et c'est plus simple comme ça, un modification sera facile si besoin. 

class Cell
{
public:
	wint_t character;
	ColorPair color;
	Attr attr;

	Cell();
	Cell(cchar_t);
	Cell(wint_t, ColorPair color = ColorPair::Default, Attr attr = Attr::Normal);
	operator cchar_t() const;
};

#endif
