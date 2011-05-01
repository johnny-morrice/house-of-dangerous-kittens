#ifndef __PLAYER__

#define __PLAYER__

#include <SDL/SDL.h>

#include "input.h"
#include "entity.h"
#include "timetrack.h"
#include "level.h"
#include "draw.h"

typedef struct Player Player;

Player * new_player();

void free_player(Player * player);

// Respond to user input
void player_user_input_response(Player * player, InputState * is, Camera * cam);

Entity * player_entity(Player * player);

#endif
