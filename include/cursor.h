#ifndef __CURSOR__

#define __CURSOR__

#include "sprite.h"
#include "input.h"

#include <SDL/SDL.h>

SDL_Surface * load_cursor();

void draw_cursor(InputState * is, SDL_Surface * cursor, SDL_Surface * screen);

#endif
