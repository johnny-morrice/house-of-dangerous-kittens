#include <glib.h>
#include <stdlib.h>
#include <math.h>

#include "look.h"
#include "zone.h"

unsigned int
look(float x, float y, float lookx, float looky)
{

	gboolean dir_hoz;

	unsigned int dir;

	// Are we going horizontally or vertically?
	if (abs(x - lookx) > abs(y - looky))
	{
		dir_hoz = TRUE;
	}
	else
	{
		dir_hoz = FALSE;
	}

	if (dir_hoz)
	{
		if (lookx > x)
		{
			dir = RIGHT;
		}
		else
		{
			dir = LEFT;
		}
	}
	else
	{
		if (looky > y)
		{
			dir = DOWN;
		}
		else
		{
			dir = UP;
		}
	}
	
	return dir;
}

float *
new_coord(float x, float y)
{
	float * coord = (float *) zone(sizeof(float) * 2);
	coord[0] = x;
	coord[1] = y;
	return coord;
}

// Crude raytrace, note squares in bounds
GSList *
raytrace(Level world, GSList * seen, float x, float y, float theta)
{
	float dx;
	float dy;

	dx = cos(theta);
	dy = sin(theta);

	while (in_bounds(world, x, y))
	{
		seen = g_slist_prepend(seen, new_coord(x, y));
		x += dx;
		y += dy;
	}

	return seen;

}

// Find squares that can be seen
GSList *
line_of_sight(Level world, float x, float y)
{
	unsigned int i;
	float angle;

	const float pi = 3.141592;
	float twopi;
	float inc;

	GSList * seen;

	seen = NULL;
	twopi = pi * 2;
	inc = twopi / 360;
	angle = 0;

	for (i = 0; i < 360; i++)
	{
		seen = raytrace(world, seen, x, y, angle);
		angle += inc;
	}

	return seen;
}

struct PointSight
{
	float targetx, targety;
	gboolean can_see;
};

void
check_sight(gpointer coordp, gpointer sightp)
{
	float * coord;
	float x;
	float y;
	struct PointSight * sight;

	sight = (struct PointSight *) sightp;

	if (!sight->can_see)
	{
		coord = (float *) coordp;
		x = coord[0];
		y = coord[1];
		sight->can_see = floor(x) == floor(sight->targetx) && floor(y) == floor(sight->targety);
	}
}

gboolean
can_see(Level world, float x, float y, float px, float py)
{
	struct PointSight sight;
	GSList * seen = line_of_sight(world, x, y);

	sight.can_see = FALSE;
	sight.targetx = px;
	sight.targety = py;

	g_slist_foreach(seen, &check_sight, &sight);

	free_seen(seen);

	return sight.can_see;
}

void
free_coord(gpointer coord, gpointer crap)
{
	free(coord);
}

// Free list of seen squares
void
free_seen(GSList * seen)
{
	g_slist_foreach(seen, &free_coord, NULL);
	g_slist_free(seen);
}
