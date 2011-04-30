#include "level.h"
#include "zone.h"
#include "sprite.h"
#include "player.h"
#include "control.h"
#include "entity.h"
#include "draw.h"

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
	char i, j;
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
	char i;

	for (i = 0; i < level_width; i++)
	{
		free(rows[i]);
	}

	free(rows);
}

void
level_set_square(Level world, char x, char y, char type)
{
	SDL_Surface * sprite = NULL;

	Square * pos = &world[x][y];
	
	pos->type = type;
	
	if (type == 'c')
	{
		sprite = load_sprite("data/sprites/level/carpet.bmp");
	}

	pos->sprite = sprite;

}

void
level_draw(Level world, SDL_Surface * canvas)
{
	char i, j;
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
