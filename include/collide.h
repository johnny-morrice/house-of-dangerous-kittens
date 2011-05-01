#ifndef __COLLIDE__

#define __COLLIDE__

#include <glib.h>

// Does a square with top left at (x,y) collide with a square with top left at (ax, ay)
gboolean collide(float x, float y, float ax, float ay);

#endif
