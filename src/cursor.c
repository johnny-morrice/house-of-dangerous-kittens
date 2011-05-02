#include "sprite.h"
#include "input.h"

#include <SDL/SDL.h>

#ifdef __WINDOWS__
#define CURSOR_PATH "data\\sprites\\cursor.png"
#else
#define CURSOR_PATH "data/sprites/cursor.png"
#endif

SDL_Surface *
load_cursor()
{
	SDL_ShowCursor(0);
	return load_sprite(CURSOR_PATH);
}

void
draw_cursor(InputState * is, SDL_Surface * cursor, SDL_Surface * screen)
{
	unsigned int x;
	unsigned int y;

	SDL_Rect dst;

	mouse_position(is, &x, &y);

	dst.x = x;
	dst.y = y;

	SDL_BlitSurface(cursor, NULL, screen, &dst);
}
