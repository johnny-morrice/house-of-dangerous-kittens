#include "sprite.h"

#include <SDL/SDL.h>
#include <string.h>

SDL_Surface *
load_sprite(const char * path)
{
	SDL_Surface * unoptimized;
	SDL_Surface * optimized;

	const char * data_path = strcat((char *) "data/sprites/", path);

	unoptimized = SDL_LoadBMP(data_path);

	optimized = SDL_DisplayFormat(unoptimized);

	SDL_FreeSurface(unoptimized);

	return optimized;
}
