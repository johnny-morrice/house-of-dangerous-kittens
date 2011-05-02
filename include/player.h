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

#endif
