#ifndef __TIMETRACK__

#define __TIMETRACK__

typedef struct TimeTracker TimeTracker;

TimeTracker * new_time_tracker();

// We're done drawing that frame 
void frame_done(TimeTracker * time);

// Frames per second
unsigned int fps(TimeTracker * time);

#endif
