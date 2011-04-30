#include "draw.h"

#include <SDL/SDL.h>
	
void
draw(SDL_Surface * sprite, SDL_Surface * canvas, float x, float y)
{
	SDL_Rect offset;
	offset.x = x * square_size;
	offset.y = y * square_size;
	SDL_BlitSurface(sprite, NULL, canvas, &offset);
}
