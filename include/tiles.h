#ifndef __TILES__

#define __TILES__

#include <SDL/SDL.h>

typedef struct TileManager TileManager;

TileManager * load_tiles();

SDL_Surface * tile_carpet(TileManager * tiles);

void
free_tiles(TileManager * tiles);

#endif