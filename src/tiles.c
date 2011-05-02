/* Copyright 2011 John Morrice
 *
 * Contact spoon@killersmurf.com
 *
 * This file is part of Dangerous Kittens.
 *
 * Dangerous Kittens is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dangerous Kittens is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dangerous Kittens.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
