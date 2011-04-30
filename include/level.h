#ifndef __LEVEL__

#define __LEVEL__

#include <SDL/SDL.h>

typedef char ** Level; 

const unsigned int level_width = 32;
const unsigned int level_height = 24;

const unsigned char carpet = 'o';

Level new_level();

// Set the tile at this square
void level_set_square(Level level, char x, char y, char type);

void free_level(Level level);

void level_draw(Level level, SDL_Surface * canvas);

#endif
