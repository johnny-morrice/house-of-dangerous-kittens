#ifndef __PLAYER__

#define __PLAYER__

#include <SDL/SDL.h>
#include <glib.h>

#include "input.h"
#include "entity.h"
#include "timetrack.h"
#include "level.h"
#include "draw.h"

typedef struct Player Player;

// Create a new player, register the players entity with the set
Player * new_player(EntitySet * others, Camera * cam, InputState * is);

// Respond to user input
void player_user_input_response(gpointer player);

Entity * player_entity(Player * player);

#endif
