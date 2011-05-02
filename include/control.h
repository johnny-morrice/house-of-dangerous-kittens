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

#ifndef __CONTROL__

#define __CONTROL__

#include "input.h"

#include <glib.h>

typedef struct Control Control;

Control * new_control();

// Should the app quit?
gboolean running(Control * halter);

// Is the game still on?
gboolean playing(Control * halter);

// Stop the game (not the program)
void stop(Control * halter);

gboolean is_paused(Control * halter);

// The game is on
void play(Control * halter);

void check_pause(Control * halter, InputState * is);

void check_exit(Control * halter, InputState * is);

#endif
