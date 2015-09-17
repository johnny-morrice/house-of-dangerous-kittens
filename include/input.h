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

#ifndef __INPUT__

#define __INPUT__

#include <SDL/SDL.h>
#include <glib.h>

#include "draw.h"

typedef struct InputState InputState;

InputState * new_input_state(void);

void update_input(InputState * is);

// Is that key down?
gboolean key_down(InputState * is, SDLKey key);

// Get the mouse position on the screen
void mouse_position(InputState * is, unsigned int * x, unsigned int * y);

// Did the user request quit?
char quit_happened(InputState * is);

void free_input(InputState * is);

gboolean mouse_press(InputState * is);

#endif
