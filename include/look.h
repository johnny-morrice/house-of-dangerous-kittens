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

#ifndef __LOOK__

#define __LOOK__

#include <glib.h>

#include "level.h"

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3


// In which of the above directions do we face if we are at (x,y)
// and are looking at (lx, ly)?
unsigned int look(float x, float y, float lx, float ly);

gboolean ** new_seen_grid();

void free_seen_grid(gboolean ** seen);

// Note where we can see 
void line_of_sight(Level world, gboolean ** seen, float x, float y);

// Standing at (x,y), can you see (px, py)?
gboolean can_see(Level world, float x, float y, float px, float py);

// Given a grid, can we see this location?
gboolean can_see_grid(gboolean ** seen, unsigned int x, unsigned int y);

#endif
