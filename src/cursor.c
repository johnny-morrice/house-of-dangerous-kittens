#include "sprite.h"
#include "input.h"

#include <SDL/SDL.h>

SDL_Surface *
load_cursor()
{
	SDL_ShowCursor(0);
	return load_sprite("data/sprites/cursor.png");
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
