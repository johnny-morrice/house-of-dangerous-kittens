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

#ifndef __TIMETRACK__

#define __TIMETRACK__

#include <glib.h>

typedef struct TimeTracker TimeTracker;

typedef struct Expirer Expirer;

Expirer * new_expirer(unsigned int freq);

gboolean expired(Expirer * timer);

TimeTracker * new_time_tracker(void);

// We're done drawing that frame 
void frame_done(TimeTracker * time);

// Frames per second
unsigned int fps(TimeTracker * time);

#endif
