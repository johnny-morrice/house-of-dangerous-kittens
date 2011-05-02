#include "tiles.h"
#include "sprite.h"
#include "zone.h"

#include <SDL/SDL.h>

#define CARPET_PATH "data/sprites/level/carpet.png"
#define STONE_PATH "data/sprites/level/stone.png"
#define WOOD_PATH "data/sprites/level/wood.png"

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
	tiles->carpet = load_sprite(CARPET_PATH);
	tiles->stone = load_sprite(STONE_PATH);
	tiles->wood = load_sprite(WOOD_PATH);
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
