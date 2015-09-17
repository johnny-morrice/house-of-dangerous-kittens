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

#ifndef __TILES__

#define __TILES__

#include <SDL/SDL.h>

typedef struct TileManager TileManager;

TileManager * load_tiles(void);

SDL_Surface * tile_carpet(TileManager * tiles);

SDL_Surface * tile_wood(TileManager * tiles);

SDL_Surface * tile_stone(TileManager * tiles);

void
free_tiles(TileManager * tiles);

#endif
