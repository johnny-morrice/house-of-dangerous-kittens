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

#ifndef __KITTEN__

#define __KITTEN__

#include "level.h"
#include "player.h"
#include "draw.h"
#include "timetrack.h"
#include "entity.h"

#include <glib.h>
#include <SDL/SDL.h>

typedef struct KittenManager KittenManager;

typedef struct Kitten Kitten;

// Spawn more kittens, somewhere in the level that we can't see!
void spawn_more_kittens(KittenManager * litter, gboolean ** seen);

// Create a kitten
Entity *
clone_kitten(KittenManager * litter, float x, float y);

// Load the kittens from the sprites
KittenManager *
load_kittens(Entity * player, Level world, TimeTracker * time, EntitySet * others);

// Free the litter
void
free_kittens(KittenManager * litter);

// Move the kitten toward the player
void
kitten_move(gpointer kitty);

#endif
