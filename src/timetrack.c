#include "timetrack.h"
#include "zone.h"

#include <SDL/SDL.h>

struct TimeTracker
{
	unsigned int last_frame;
};

TimeTracker *
new_time_tracker()
{
	TimeTracker * time = (TimeTracker *) zone(sizeof(TimeTracker));
	frame_done(time);
	return time;
}

// This frame has been finished
void
frame_done(TimeTracker * time)
{
	time->last_frame = SDL_GetTicks();
}

// How long has it taken to render this frame?
unsigned int
frame_ms(TimeTracker * time)
{
	return SDL_GetTicks() - time->last_frame;
}

