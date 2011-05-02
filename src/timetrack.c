#include "timetrack.h"
#include "zone.h"

#include <SDL/SDL.h>

struct TimeTracker
{
	unsigned int first_time;
	unsigned int frames;
	unsigned int fps;
};

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
