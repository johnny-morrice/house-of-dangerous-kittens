#include "sprite.h"

#include <SDL/SDL.h>

SDL_Surface *
load_sprite(const char * path)
{
	SDL_Surface * unoptimized;
	SDL_Surface * optimized;

	unoptimized = SDL_LoadBMP(path);

	optimized = SDL_DisplayFormat(unoptimized);

	SDL_FreeSurface(unoptimized);

	return optimized;
}
