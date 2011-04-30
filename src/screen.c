#include "screen.h"

#include <SDL/SDL.h>

// Setup SDL.
// Return the screen.
SDL_Surface *
init_sdl()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	return SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
}
