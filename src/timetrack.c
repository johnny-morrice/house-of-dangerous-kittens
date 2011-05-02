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

#include "timetrack.h"
#include "zone.h"

#include <SDL/SDL.h>
#include <glib.h>

struct Expirer
{
	float last;
	float freq; 
};

struct TimeTracker
{
	unsigned int first_time;
	unsigned int frames;
	unsigned int fps;
};

Expirer *
new_expirer(unsigned int freq)
{
	Expirer * timer = (Expirer *) zone(sizeof(Expirer));
	timer->last = SDL_GetTicks();
	timer->freq = (float) freq;
	return timer;
}

// Has the timer expired?
gboolean
expired(Expirer * timer)
{
	float ticks = (float) SDL_GetTicks();
	if ((ticks - timer->last) / 1000.0 > 1.0 / timer->freq)
	{
		timer->last = ticks;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

TimeTracker *
new_time_tracker()
{
	TimeTracker * time = (TimeTracker *) zone(sizeof(TimeTracker));
	time->frames = 0;
	time->fps = 100;
	time->first_time = SDL_GetTicks();

	return time;
}

// This frame has been finished
void
frame_done(TimeTracker * time)
{
	unsigned int ticks = SDL_GetTicks();
	time->frames ++;
	if (ticks - time->first_time > 1000)
	{
		time->first_time = ticks;
		time->fps = time->frames;
		time->frames = 0;
	}
}

// Get the fps
unsigned int
fps(TimeTracker * time)
{
	return time->fps;
}
