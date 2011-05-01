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
walkable_square(Level world, float x, float y)
{
	unsigned int rx, ry;

	rx = floor(x);
	ry = floor(y);

	return world[rx][ry].type == 'c';
}

gboolean
walkable(Level world, float x, float y)
{
	return walkable_square(world, x, y) && walkable_square(world, x + 1, y) && walkable_square(world, x, y + 1);
}

gboolean
in_bounds(Level world, float x, float y)
{
	if (x >= 0 && y >= 0 && x < level_width - 1 && y < level_height - 1)
	{
		return walkable(world, x, y);
	}
	else
	{
		return FALSE;
	}
}
