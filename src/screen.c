#include "screen.h"

#include <SDL/SDL.h>

// Setup SDL.
// Return the screen.
SDL_Surface *
init_sdl()
{
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	return SDL_SetVideoMode(screen_width, screen_height, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
}

void
shutdown_sdl()
{
	SDL_Quit();
}
