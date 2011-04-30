#include "sprite.h"

#include <SDL/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Surface *
load_sprite(const char * path)
{
	SDL_Surface * unoptimized;
	SDL_Surface * optimized;

	unoptimized = IMG_Load(path);

	if (! unoptimized)
	{
		fprintf(stderr, "Could not load image '%s'\n.", path);
		exit(EXIT_FAILURE);
	}

	optimized = SDL_DisplayFormatAlpha(unoptimized);

	SDL_FreeSurface(unoptimized);

	return optimized;
}
