#include "level.h"
#include "zone.h"
#include "sprite.h"
#include "player.h"
#include "control.h"
#include "entity.h"
#include "draw.h"

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
level_set_square(Level world, int x, int y, char type)
{
	SDL_Surface * sprite = NULL;

	Square * pos = &world[x][y];
	
	pos->type = type;
	
	if (type == 'c')
	{
		sprite = load_sprite("data/sprites/level/carpet.png");
	}

	pos->sprite = sprite;

}

void
level_draw(Level world, SDL_Surface * canvas)
{
	int i, j;
	Square sq;

	for (i = 0; i < level_width; i++)
	{
		for (j = 0; j < level_height; j++)
		{
			sq = world[i][j];
			draw(sq.sprite, canvas, i, j);
		}
	}
}

gboolean
walkable(char type)
{
	return type == 'c';
}

gboolean
in_bounds(Level world, float x, float y)
{
	int rx, ry;
	char type;

	rx = (char) floor(x);
	ry = (char) floor(y);

	if (rx >= 0 && ry >= 0 && rx < level_width - 1 && ry < level_height - 1)

	{
		type = world[rx][ry].type;
		return walkable(type);
	}
	else
	{
		return FALSE;
	}
}
