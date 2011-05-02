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

#ifndef __DRAW__

#define __DRAW__

#include <SDL/SDL.h>

// Size of each tile in pixels
#define square_size 64

typedef struct Camera Camera;

Camera *
new_camera();

// Center the camera on this position
void
camera_centre(Camera * cam, float x, float y);

// Transform the coordinates with the camera
void
camera_transform(Camera * cam, float x, float y, float * tx, float * ty);

// Inverse of the camera transform
void camera_inverse_transform(Camera * cam, float x, float y, float * tx, float * ty);

void
draw(SDL_Surface * thing, SDL_Surface * canvas, Camera * cam, float x, float y);


#endif
