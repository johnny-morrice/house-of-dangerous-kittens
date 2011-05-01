#include "screen.h"

#include <SDL/SDL.h>

// Setup SDL.
// Return the screen.
SDL_Surface *
init_sdl()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	return SDL_SetVideoMode(screen_width, screen_height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
}

// Create new surface
//SDL_Surface *
//new_canvas()
//{
//	return SDL_CreateRGBSurface(SDL_HWSURFACE, screen_width, screen_height, 32, 0 0 0, 0);
//}
