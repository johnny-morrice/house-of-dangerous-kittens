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

#ifndef __PLAYER__

#define __PLAYER__

#include <SDL/SDL.h>
#include <glib.h>

#include "input.h"
#include "entity.h"
#include "timetrack.h"
#include "level.h"
#include "draw.h"
#include "control.h"

typedef struct Player Player;

// Create a new player, register the players entity with the set
Player * new_player(EntitySet * others, Camera * cam, InputState * is, Level world, Control * halter);

// Respond to user input
void player_user_input_response(gpointer player);

Entity * player_entity(Player * player);

// Hurt the player
void
player_hurt(Player * me);

// The player's health
unsigned int
player_health(Player * me);

unsigned int
player_score(Player * me);

#endif
