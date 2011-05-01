#include "tiles.h"
#include "sprite.h"
#include "zone.h"

#include <SDL/SDL.h>

struct TileManager
{
	SDL_Surface * carpet;
};

TileManager *
load_tiles()
{
	TileManager * tiles = (TileManager *) zone(sizeof(TileManager));
	tiles->carpet = load_sprite("data/sprites/level/carpet.png");
	return tiles;
}

SDL_Surface *
tile_carpet(TileManager * tiles)
{
	return tiles->carpet;
}

void
free_tiles(TileManager * tiles)
{
	SDL_FreeSurface(tiles->carpet);
	free(tiles);
}
