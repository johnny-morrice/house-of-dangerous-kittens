#ifndef __DRAW__

#define __DRAW__

#include <SDL/SDL.h>

// Size of each tile in pixels
#define square_size 64

void
draw(SDL_Surface * thing, SDL_Surface * canvas, float x, float y);


#endif
