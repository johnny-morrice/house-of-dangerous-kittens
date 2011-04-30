#include "level.h"
#include "zone.h"

#include <SDL/SDL.h>

Level new_level()
{
	char i, j;
	Level rows;
	char * col;

	rows = (Level) zone(sizeof(char *) * level_width);

	for (i = 0; i < level_width; i++)
	{
		col = (char *) zone(sizeof(char *) * level_height);
		rows[i] = col;
		for (j = 0; j < level_height; j++)
		{
			col[j] = ' ';
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
	world[x][y] = type;
}
