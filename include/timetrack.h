#ifndef __TIMETRACK__

#define __TIMETRACK__

#include <glib.h>

typedef struct TimeTracker TimeTracker;

typedef struct Expirer Expirer;

Expirer * new_expirer(unsigned int freq);

gboolean expired(Expirer * timer);

TimeTracker * new_time_tracker();

// We're done drawing that frame 
void frame_done(TimeTracker * time);

// Frames per second
unsigned int fps(TimeTracker * time);

#endif
