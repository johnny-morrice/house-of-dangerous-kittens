#ifndef __LEVEL__

#define __LEVEL__

#include <SDL/SDL.h>
#include <glib.h>

#include "screen.h"
#include "draw.h"
#include "tiles.h"

typedef struct Square Square;

typedef Square ** Level; 


#define level_width 30
#define level_height 30

#define square_carpet 'c'
#define square_empty ' '

Level new_level();

// Load a level from a file
void load_level(Level world, TileManager * tiles, const char * path);

// Set the tile at this square
void level_set_square(Level level, TileManager * tiles, int x, int y, char type);

void free_level(Level level);

// Draw parts of the level the entity can see onto the canvas
void level_draw(Level level, SDL_Surface * canvas, Camera * cam, gboolean ** seen);

// Is a point at this position in bounds
gboolean point_in_bounds(Level level, float x, float y);

// Is a square with top left at this position in bounds?
gboolean in_bounds(Level level, float x, float y);

#endif
