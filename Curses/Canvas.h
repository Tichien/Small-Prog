#ifndef _CANVAS_H_
#define _CANVAS_H_
/*
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
*/
#include "Term.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS CANVAS

class Canvas : public Window {

protected:
	Vector2i m_pixel_size;

public:

/* initialise un canvas qui fait la taille de l'ecran */
	Canvas();
	Canvas(int w, int h);
	virtual ~Canvas();

	//faire attention au fuite mémoire avec set unset et toggle acces dans des (lecture de variable non init) 

/* place un pixel a la position "point" */
	void set(int x, int y);
	void set(const Vector2i& point);
	
/* enleve le pixel qui ce trouve a la position "point" */
	void unset(int x, int y);
	void unset(const Vector2i& point);

/* place un pixel a la position "point" du canvas si il n'y est pas deja, sinon l'enleve */
	void toggle(int x, int y);
	void toggle(const Vector2i& point);

/* Renvoie les dimension du canvas en nombre de pixel (width, height) */
	Vector2i get_size() const;

/* affiche la zone "offset" du canvas à la position "position" qui est (0, 0) par default */
	virtual void display();
	void display(const Vector2i& position);
	void display(const Vector2i& position, const IntRect& offset);

/* verifie si le pixel a la position point existe */
	bool is_set(int x, int y);
	bool is_set(const Vector2i& point);
};

/* Converti la position du pixel (x, y) en coordonnée de cellule (row, col) */
Vector2i pixel_to_cell_coord(int x, int y);
Vector2i pixel_to_cell_coord(const Vector2i& point);

/* Converti les coordonnées de la cellule (row, col) en position de pixel (x, y) */
Vector2i cell_to_pixel_pos(int col, int row);
Vector2i cell_to_pixel_pos(const Vector2i& cell_coord);

/* verifie si le wide character "wch" est du braille */
bool is_braille(wint_t wch);

/* dessine une ligne sur le canvas allant du point p1 au point p2 */
void draw_line(Canvas& canvas, int x1, int y1, int x2, int y2);
void draw_line(Canvas& canvas, const Vector2i& p1, const Vector2i p2);

#endif
