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

#include "screen.h"

#include <SDL/SDL.h>

// Setup SDL.
// Return the screen.
SDL_Surface *
init_sdl(void)
{
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	return SDL_SetVideoMode(screen_width, screen_height, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
}

void
shutdown_sdl(void)
{
	SDL_Quit();
}
