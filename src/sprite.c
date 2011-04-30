#include "sprite.h"

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Surface *
load_sprite(const char * path)
{
	SDL_Surface * unoptimized;
	SDL_Surface * optimized;

	unoptimized = SDL_LoadBMP(path);

	if (! unoptimized)
	{
		fprintf(stderr, "Could not load bitmap\n.");
		exit(EXIT_FAILURE);
	}

	optimized = SDL_DisplayFormat(unoptimized);

	SDL_FreeSurface(unoptimized);

	return optimized;
}
