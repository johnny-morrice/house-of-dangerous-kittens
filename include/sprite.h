#ifndef __SPRITE__

#define __SPRITE__

#include <SDL/SDL.h>

// Load a sprite, given a path relative to data/sprites/
SDL_Surface * load_sprite(const char * sprite_path);

#endif
