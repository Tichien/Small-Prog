
void draw_line1(Canvas& canvas, int x1, int y1, int x2, int y2){

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

void draw_line1(Canvas& canvas, const Vector2i& p1, const Vector2i p2){
	draw_line1(canvas, p1.x, p1.y, p2.x, p2.y);
}