#ifndef __LEVEL__

#define __LEVEL__

#include <SDL/SDL.h>

#include "screen.h"

typedef struct Square Square;

typedef Square ** Level; 

const unsigned char square_size = 32; 
const unsigned char level_width = screen_width / square_size;
const unsigned char level_height = screen_height / square_size;

const unsigned char square_carpet = 'c';
const unsigned char square_empty = ' ';

Level new_level();

// Set the tile at this square
void level_set_square(Level level, char x, char y, char type);

void free_level(Level level);

// Draw the level onto the canvas
void level_draw(Level level, SDL_Surface * canvas);

#endif
