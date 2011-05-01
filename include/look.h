#ifndef __LOOK__

#define __LOOK__

#include "glib.h"

#include "level.h"

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3


// In which of the above directions do we face if we are at (x,y)
// and are looking at (lx, ly)?
unsigned int look(float x, float y, float lx, float ly);

// Return a list of cells that we can see
GSList *
line_of_sight(Level world, float x, float y);

// Standing at (x,y), can you see (px, py)?
gboolean can_see(Level world, float x, float y, float px, float py);

void free_seen(GSList * seen);

#endif
