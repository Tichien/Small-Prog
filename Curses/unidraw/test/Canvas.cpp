#include "Canvas.h"

////////////////////////////////////////////////// VARIABLES STATIQUES

const wint_t braille_char_offset = 0x2800;

const int pixel_map[4][2] = { 	{0x01, 0x08}, 
{0x02, 0x10},
{0x04, 0x20},
{0x40, 0x80} };

////////////////////////////////////////////////// CONSTRUCTEURS

Canvas::Canvas(){
	int h = 0, w = 0;

	getmaxyx(stdscr, h, w);

	m_frame = newpad(h, w);
}

Canvas::Canvas(int w, int h){
	//int col, row;
	/* converti le nombre de pixels en nombre de colonnes/lignes */
	//newpad(0, 0); fille the entire terminal
	//pixel_to_cell_coord(w, h, col, row);
	if(!(w % 2 == 0))
		w+=2;
	if(!(h % 4 == 0)) 
		h+=4;
	
	m_frame = newpad(h / 4, w / 2);
} 

Canvas::~Canvas(){
	delwin(m_frame);
}

////////////////////////////////////////////////// METHODES

void Canvas::set(int x, int y){

	Vector2i cell_coord = pixel_to_cell_coord(x, y);

	wint_t cell = get_cell(cell_coord);

	if(!is_braille(cell))
		cell = braille_char_offset;

	cell |= pixel_map[y % 4][x % 2];
 
	set_cell(cell_coord, cell);
}

void Canvas::set(const Vector2i& point){
	set(point.x, point.y);
}

void Canvas::unset(int x, int y){

	Vector2i cell_coord = pixel_to_cell_coord(x, y);

	wint_t cell = get_cell(cell_coord);

	if(!is_braille(cell))
		return;

	cell &= ~pixel_map[y % 4][x % 2];

	set_cell(cell_coord, cell);
}

void Canvas::unset(const Vector2i& point){
	unset(point.x, point.y);
}

void Canvas::toggle(int x, int y){

	wint_t cell = get_cell(pixel_to_cell_coord(x, y));

	if(is_braille(cell) && cell & pixel_map[y % 4][x % 2])
		unset(x, y);
	else
		set(x, y);
}

void Canvas::toggle(const Vector2i& point){
	toggle(point.x, point.y);
}

wint_t Canvas::get_cell(int row, int col) const {
	wchar_t wc[2] = {0};
	mvwinnwstr(m_frame, row, col, wc, 1);
	return wc[0];
}

wint_t Canvas::get_cell(const Vector2i& cell_coord) const {
	return get_cell(cell_coord.x, cell_coord.y);
}

void Canvas::set_cell(int row, int col, wint_t c){
	wchar_t wc[2] = {0}; wc[0] = c;
	mvwaddnwstr(m_frame, row, col, wc, 1);
}

void Canvas::set_cell(const Vector2i& cell_coord, wint_t c){
	set_cell(cell_coord.x, cell_coord.y, c);
}

Vector2i Canvas::get_size() const {
	int h = 0, w = 0;
	getmaxyx(m_frame, h, w);
	return Vector2i(w * 2, h * 4);
}

void Canvas::write(int x, int y, const std::string& text){
	mvwprintw(m_frame, y, x, text.c_str());
}

void Canvas::write(const Vector2i& position, const std::string& text){
	write(position.x, position.y, text);
}

void Canvas::clear(int col, int row, int w, int h){
	wclear(m_frame);
}

void Canvas::display(){
	int h, w;
	getmaxyx(stdscr, h, w);

	display(Vector2i::zero, IntRect(Vector2i::zero, Vector2i(w, h)));
}

void Canvas::display(const Vector2i& position, const IntRect& offset){
	int h, w;
	getmaxyx(stdscr, h, w);

	int maxY = position.y + offset.height - 1;
	int maxX = position.x + offset.width - 1;
	int maxTermY = h - 1;
	int maxTermX = w - 1;

	int pminrow = position.y >= 0 ? offset.y : offset.y - position.y;
	int pmincol = position.x >= 0 ? offset.x : offset.x - position.x;
	int sminrow = offset.y >= 0 ? position.y : position.y - offset.y;
	int smincol = offset.x >= 0 ? position.x : position.x - offset.x;
	int smaxrow = maxTermY >= maxY ? maxY : maxY - (maxY - maxTermY);
	int smaxcol = maxTermX >= maxX ? maxX : maxX - (maxX - maxTermX);

	prefresh(m_frame, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol);
}

bool Canvas::is_set(int x, int y){
	wint_t cell = get_cell(pixel_to_cell_coord(x, y));
	return is_braille(cell) && cell & pixel_map[y % 4][x % 2];
}

////////////////////////////////////////////////// FONCTIONS

Vector2i pixel_to_cell_coord(int x, int y){
	return Vector2i(y / 4, x / 2);
}

Vector2i pixel_to_cell_coord(const Vector2i& point){
	return pixel_to_cell_coord(point.x, point.y);
}

bool is_braille(wint_t cell){
	return cell >= 0x2800 && cell <= 0x28FF;
}

/* version plus simple de draw_line mais un peu moins precise */
void draw_line1(Canvas& canvas, int x1, int y1, int x2, int y2){

	int xdiff = std::max(x1, x2) - std::min(x1, x2);
	int ydiff = std::max(y1, y2) - std::min(y1, y2);
	int xdir = x1 <= x2 ? 1 : -1;
	int ydir = y1 <= y2 ? 1 : -1;

	int r = std::max(xdiff, ydiff);

	for (int i = 0; i < r + 1; ++i){
		int x = x1;
		int y = y1;

		if (ydiff)
			y += (float(i) * ydiff) / r * ydir;
		if (xdiff)
			x += (float(i) * xdiff) / r * xdir;

		canvas.set(x, y);
	}
}

void draw_line(Canvas& canvas, const Vector2i& p1, const Vector2i p2){
	draw_line(canvas, p1.x, p1.y, p2.x, p2.y);
}

void draw_line(Canvas& canvas, int x1, int y1, int x2, int y2){

	int dx = x2 - x1;
	int dy = y2 - y1;

	if(dx != 0){
		if(dx > 0){
			if(dy != 0){
				if(dy > 0){
					// vecteur oblique dans le 1er quadran
					
					if(dx >= dy){
						// vecteur diagonal ou oblique proche de l’horizontale dans le 1er octant

						float e = dx ;
						dx = e * 2;
						dy *= 2;

						while(1){
							canvas.set(x1, y1);

							if((x1++) == x2)
								break;

							if((e -= dy) < 0){
								y1++;
								e += dx;
							}
						}
					}
					else{
						// vecteur oblique proche de la verticale, dans le 2d octant
						
						float e = dy;
						dy = e * 2;
						dx *= 2;

						while(1){
							canvas.set(x1, y1);

							if((y1++) == y2)
								break;

							if((e -= dx) < 0){
								x1++;
								e += dy;
							}
						}
					}
				}
				else{
					// vecteur oblique dans le 4e cadran
					
					if(dx >= -dy){
						// vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
						float e = dx;
						dx = e * 2;
						dy *= 2;

						while(1){
							canvas.set(x1, y1);

							if((x1++) == x2)
								break;

							if((e += dy) < 0){
								y1--;
								e += dx;
							}
						}
					}
					else{
						// vecteur oblique proche de la verticale, dans le 7e octant
						
						float e = dy;
						dy = e * 2;
						dx *= 2;

						while(1){
							canvas.set(x1, y1);

							if((y1--) == y2)
								break;

							if((e += dx) > 0){
								x1++;
								e += dy;
							}
						}
					}
				}
			}
			else{
				// vecteur horizontal vers la droite
				
				do{
					canvas.set(x1, y1);
				}while(!((x1++) == x2));
			}
		}
		else{
			if(dy != 0){
				if(dy > 0){
					// vecteur oblique dans le 2d quadran
					
					if(-dx >= dy){
						// vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
						
						float e = dx;
						dx = e * 2;
						dy *= 2;

						while(1){
							canvas.set(x1, y1);

							if((x1--) == x2)
								break;

							if((e += dy) >= 0){
								y1++;
								e += dx;
							}
						}
					}
					else{
						// vecteur oblique proche de la verticale, dans le 3e octant
						
						float e = dy;
						dy = e * 2;
						dx *= 2;

						while(1){
							canvas.set(x1, y1);

							if((y1++) == y2)
								break;

							if((e += dx) <= 0){
								x1--;
								e += dy;
							}
						}
					}
				}
				else{
					// vecteur oblique dans le 3e cadran
					
					if(dx <= dy){
						// vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
						
						float e = dx;
						dx = e * 2;
						dy *= 2;

						while(1){
							canvas.set(x1, y1);

							if((x1--) == x2)
								break;

							if((e -= dy) >= 0){
								y1--;
								e += dx;
							}
						}
					}
					else{
						// vecteur oblique proche de la verticale, dans le 6e octant
						
						float e = dy;
						dy = e * 2;
						dx *= 2;

						while(1){
							canvas.set(x1, y1);

							if((y1--) == y2)
								break;

							if((e -= dx) >= 0){
								x1--;
								e += dy;
							}
						}
					}
				}
			}
			else{
				// vecteur horizontal vers la gauche
				
				do{
					canvas.set(x1, y1);
				}while(!((x1--) == x2));
			}
		}
	}
	else{
		if(dy != 0){
			if(dy > 0){
				// vecteur vertical croissant
				
				do{
					canvas.set(x1, y1);
				}while(!((y1++) == y2));
			}
			else{
				// vecteur vertical décroissant
				
				do{
					canvas.set(x1, y1);
				}while(!((y1--) == y2));
			}
		}
	}
}