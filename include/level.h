#ifndef __LEVEL__

#define __LEVEL__

#include <SDL/SDL.h>
#include <glib.h>

#include "screen.h"
#include "draw.h"

typedef struct Square Square;

typedef Square ** Level; 


#define level_width (screen_width / square_size)
#define level_height (screen_height / square_size)

#define square_carpet 'c'
#define square_empty ' '

Level new_level();

// Set the tile at this square
void level_set_square(Level level, int x, int y, char type);

void free_level(Level level);

// Draw the level onto the canvas
void level_draw(Level level, SDL_Surface * canvas);

gboolean in_bounds(Level level, float x, float y);

#endif
