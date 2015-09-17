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

#include <glib.h>
#include <stdlib.h>
#include <math.h>

#include "level.h"
#include "look.h"
#include "zone.h"

unsigned int
look(float x, float y, float lookx, float looky)
{

	gboolean dir_hoz;

	unsigned int dir;

	// Are we going horizontally or vertically?
	if (abs(x - lookx) > abs(y - looky))
	{
		dir_hoz = TRUE;
	}
	else
	{
		dir_hoz = FALSE;
	}

	if (dir_hoz)
	{
		if (lookx > x)
		{
			dir = RIGHT;
		}
		else
		{
			dir = LEFT;
		}
	}
	else
	{
		if (looky > y)
		{
			dir = DOWN;
		}
		else
		{
			dir = UP;
		}
	}
	
	return dir;
}

float *
new_coord(float x, float y)
{
	float * coord = (float *) zone(sizeof(float) * 2);
	coord[0] = x;
	coord[1] = y;
	return coord;
}

// Crude raytrace, note squares in bounds
GSList *
raytrace(Level world, GSList * seen, float x, float y, float theta)
{
	float dx;
	float dy;

	dx = cos(theta);
	dy = sin(theta);

	while (point_in_bounds(world, x, y))
	{
		seen = g_slist_prepend(seen, new_coord(x, y));
		x += dx;
		y += dy;
	}

	return seen;

}

gboolean **
new_seen_grid(void)
{
	unsigned int i;

	gboolean ** grid;

	grid = (gboolean **) zone(sizeof(gboolean **) * level_width);

	for (i = 0; i < level_width; i++)
	{
		grid[i] = (gboolean *) zone(sizeof(gboolean *) * level_height);
	}

	return grid;
}

void
free_seen_grid(gboolean ** grid)
{
	unsigned int i;

	for (i = 0; i < level_width; i++)
	{
		free(grid[i]);
	}

	free(grid);
}

void
note_point(gpointer coordp, gpointer gridp)
{
	unsigned int x;
	unsigned int y;

	gboolean ** grid = (gboolean **) gridp;
	float * coord = (float *) coordp;

	x = floor(coord[0]);
	y = floor(coord[1]);

	grid[x][y] = TRUE;

}

void
free_coord(gpointer coord, gpointer crap)
{
	free(coord);
}

// Free list of seen squares
void
free_seen_list(GSList * seen)
{
	g_slist_foreach(seen, &free_coord, NULL);
	g_slist_free(seen);
}

// Note squares that can be seen
void
line_of_sight(Level world, gboolean ** grid, float x, float y)
{
	unsigned int i;
	unsigned int j;
	float angle;

	const float pi = 3.141592;
	float twopi;
	float inc;

	GSList * seen;

	seen = NULL;
	twopi = pi * 2;
	inc = twopi / 360;
	angle = 0;

	for (i = 0; i < level_width; i++)
	{
		for (j = 0; j < level_height; j++)
		{
			grid[i][j] = FALSE;
		}
	}

	for (i = 0; i < 360; i++)
	{
		seen = raytrace(world, seen, x, y, angle);
		angle += inc;
	}

	g_slist_foreach(seen, &note_point, grid);

	free_seen_list(seen);
}

gboolean
can_see(Level world, float x, float y, float px, float py)
{
	gboolean ** seen;

	gboolean can;

	unsigned int i;
	unsigned int j;

	i = floor(px);
	j = floor(py);

	seen = new_seen_grid();

	line_of_sight(world, seen, x, y);

	can = can_see_grid(seen, i, j);

	free_seen_grid(seen);

	return can;
}

gboolean
can_see_grid(gboolean ** seen, unsigned int x, unsigned int y)
{
	if (x < level_width && y < level_height)
	{
		return seen[x][y];
	}
	else
	{
		return FALSE;
	}
}


