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

#include "draw.h"
#include "zone.h"
#include "screen.h"

#include <SDL/SDL.h>

struct Camera
{
	float xoffset;
	float yoffset;
};

Camera *
new_camera(void)
{
	return (Camera *) zone(sizeof(Camera));
}

void
camera_centre(Camera * cam, float x, float y)
{
	float realx, realy;
	float centrex, centrey;
	
	realx = square_size * x;
	realy = square_size * y;

	centrex = screen_width / 2;
	centrey = screen_height / 2;

	cam->xoffset = centrex - realx;
	cam->yoffset = centrey - realy;

}

void
camera_inverse_transform(Camera * cam, float x, float y, float * tx, float * ty)
{
	*tx = x - cam->xoffset;
	*ty = y - cam->yoffset;
}


void
camera_transform(Camera * cam, float x, float y, float * tx, float * ty)
{
	*tx = x + cam->xoffset;
	*ty = y + cam->yoffset;
}

void
draw(SDL_Surface * sprite, SDL_Surface * canvas, Camera * cam, float x, float y)
{
	SDL_Rect offset;
	float realx, realy;

	camera_transform(cam, x * square_size, y * square_size, &realx, &realy);
	offset.x = realx;
	offset.y = realy;
	SDL_BlitSurface(sprite, NULL, canvas, &offset);
}
