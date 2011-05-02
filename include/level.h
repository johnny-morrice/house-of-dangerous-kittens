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

#ifndef __LEVEL__

#define __LEVEL__

#include <SDL/SDL.h>
#include <glib.h>

#include "screen.h"
#include "draw.h"
#include "tiles.h"

typedef struct Square Square;

typedef Square ** Level; 


#define level_width 30
#define level_height 30

#define square_carpet 'c'
#define square_empty ' '

Level new_level();

// Load a level from a file
void load_level(Level world, TileManager * tiles, const char * path);

// Set the tile at this square
void level_set_square(Level level, TileManager * tiles, int x, int y, char type);

void free_level(Level level);

// Draw parts of the level the entity can see onto the canvas
void level_draw(Level level, SDL_Surface * canvas, Camera * cam, gboolean ** seen);

// Is a point at this position in bounds
gboolean point_in_bounds(Level level, float x, float y);

// Is a square with top left at this position in bounds?
gboolean in_bounds(Level level, float x, float y);

#endif
