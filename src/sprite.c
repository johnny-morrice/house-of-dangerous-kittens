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

#include <SDL/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Surface *
load_sprite(const char * path)
{
	SDL_Surface * unoptimized;
	SDL_Surface * optimized;

	printf("Loading sprite %s\n", path);

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
