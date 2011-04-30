#ifndef __PLAYER__

#define __PLAYER__

#include <SDL/SDL.h>

#include "input.h"
#include "timetrack.h"
#include "level.h"

typedef struct Player Player;

Player * new_player();

void free_player(Player * player);

void player_fetch_direction(Player * player, InputState * is);

#endif
