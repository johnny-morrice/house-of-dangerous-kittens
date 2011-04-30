#ifndef __PLAYER__

#define __PLAYER__

#include <SDL/SDL.h>

#include "timetrack.h"
#include "level.h"

typedef struct Player Player;

Player * new_player();

void player_move(Player * player, Level level, TimeTracker * time);

void player_set_position(Player * player, char x, char y);

void free_player(Player * player);

void player_draw(Player * player, SDL_Surface * canvas);

void player_fetch_direction(Player * player, InputState * is);

#endif
