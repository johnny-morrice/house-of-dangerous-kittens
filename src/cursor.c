/* Copyright 2011 John Morrice
 *
 * Contact spoon@killersmurf.com
 *
 * This file is part of Dangerous Kittens.
 *
 * Dangerous Kittens is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dangerous Kittens is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dangerous Kittens.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "sprite.h"
#include "input.h"

#include <SDL/SDL.h>

#ifdef __WINDOWS__
#define CURSOR_PATH "data\\sprites\\cursor.png"
#else
#define CURSOR_PATH "data/sprites/cursor.png"
#endif

SDL_Surface *
load_cursor(void)
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
