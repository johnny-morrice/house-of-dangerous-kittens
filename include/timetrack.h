#ifndef __TIMETRACK__

#define __TIMETRACK__

typedef struct TimeTracker TimeTracker;

TimeTracker * new_time_tracker();

// We're done drawing that frame 
void frame_done(TimeTracker * time);

// The number of milliseconds it took to render this frame
unsigned int frame_ms(TimeTracker * time);

#endif
