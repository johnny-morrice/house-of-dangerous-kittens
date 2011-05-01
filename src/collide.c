#include "collide.h"

#include <glib.h>

// Does a square with top left at (x,y) collide with a square with top left at (ax, ay)
gboolean
collide(float x, float y, float ax, float ay)
{

	float alx, arx,
	      aty, aby,
	      lx, rx,
	      ty, by;

	alx = ax;
	arx = alx + 1;
	aty = ay;
	aby = aty + 1;
	lx = x;
	rx = lx + 1;
	ty = y;
	by = ty + 1;

	if (!(alx >= rx || arx <= lx || aby <= ty || aty >= by))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

