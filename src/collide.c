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

#include "collide.h"

#include <glib.h>

// Does a square with top left at (x,y) collide with a square with top left at (ax, ay)
gboolean
collide(float x, float y, float ax, float ay)
{

	float alx, arx,
	      aty, aby,
	      lx, rx,
	      ty, by;

	alx = ax;
	arx = alx + 1;
	aty = ay;
	aby = aty + 1;
	lx = x;
	rx = lx + 1;
	ty = y;
	by = ty + 1;

	if (!(alx >= rx || arx <= lx || aby <= ty || aty >= by))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

