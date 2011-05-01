#include "level.h"
#include "zone.h"
#include "sprite.h"
#include "player.h"
#include "control.h"
#include "entity.h"
#include "draw.h"
#include "tiles.h"

#include <math.h>
#include <glib.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>

struct Square
{
	SDL_Surface * sprite;
	char type;
};

Level new_level()
{
	int i, j;
	Level rows;
	Square * col;

	Square nothing;
	nothing.sprite = NULL;
	nothing.type = square_empty;

	rows = (Level) zone(sizeof(Square *) * level_width);

	for (i = 0; i < level_width; i++)
	{
		col = (Square *) zone(sizeof(Square) * level_height);
		rows[i] = col;
		for (j = 0; j < level_height; j++)
		{
			col[j] = nothing;
		}
	}

	return rows;
}

void
free_level(Level rows)
{
	int i;

	for (i = 0; i < level_width; i++)
	{
		free(rows[i]);
	}

	free(rows);
}

void
level_set_square(Level world, TileManager * tiles, int x, int y, char type)
{
	SDL_Surface * sprite = NULL;

	Square * pos = &world[x][y];
	
	pos->type = type;
	
	if (type == 'c')
	{
		sprite = tile_carpet(tiles);
	}

	pos->sprite = sprite;

}

void
level_draw(Level world, SDL_Surface * canvas, Camera * cam)
{
	int i, j;
	Square sq;

	for (i = 0; i < level_width; i++)
	{
		for (j = 0; j < level_height; j++)
		{
			sq = world[i][j];
			draw(sq.sprite, canvas, cam, i, j);
		}
	}
}

gboolean
point_in_bounds(Level world, float x, float y)
{
	int fx, fy;

	gboolean walkable;

	fx = floor(x);
	fy = floor(y);

	if (fx >= 0 && fy >= 0 && fx < level_width - 1 && fy < level_height - 1)
	{

		walkable = world[fx][fy].type == 'c';

		return walkable;
	}
	else
	{
		return FALSE;
	}
}

gboolean
in_bounds(Level world, float x, float y)
{
	return point_in_bounds(world, x, y) && point_in_bounds(world, x + 1, y) && point_in_bounds(world, x, y + 1) && point_in_bounds(world, x + 1, y + 1);
}
