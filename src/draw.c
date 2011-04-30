#include "draw.h"

#include <SDL/SDL.h>
	
void
draw(SDL_Surface * sq, SDL_Surface * canvas, char x, char y)
{
	SDL_Rect offset;
	offset.x = x * square_size;
	offset.y = y * square_size;
	SDL_BlitSurface(sq.sprite, NULL, canvas, &offset);
}
