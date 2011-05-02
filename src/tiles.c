#include "tiles.h"
#include "sprite.h"
#include "zone.h"

#include <SDL/SDL.h>

struct TileManager
{
	SDL_Surface * carpet;
	SDL_Surface * wood;
	SDL_Surface * stone;
};

TileManager *
load_tiles()
{
	TileManager * tiles = (TileManager *) zone(sizeof(TileManager));
	tiles->carpet = load_sprite("data/sprites/level/carpet.png");
	tiles->stone = load_sprite("data/sprites/level/stone.png");
	tiles->wood = load_sprite("data/sprites/level/wood.png");
	return tiles;
}

SDL_Surface *
tile_carpet(TileManager * tiles)
{
	return tiles->carpet;
}

SDL_Surface *
tile_stone(TileManager * tiles)
{
	return tiles->stone;
}

SDL_Surface *
tile_wood(TileManager * tiles)
{
	return tiles->wood;
}

void
free_tiles(TileManager * tiles)
{
	SDL_FreeSurface(tiles->carpet);
	SDL_FreeSurface(tiles->wood);
	SDL_FreeSurface(tiles->stone);
	free(tiles);
}
