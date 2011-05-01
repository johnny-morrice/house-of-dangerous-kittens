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

// Set the player's direction, with regard to the position of the mouse
void player_set_direction(Player * player, InputState * is, Camera * cam);

Entity * player_entity(Player * player);

#endif
