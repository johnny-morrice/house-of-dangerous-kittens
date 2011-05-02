#ifndef __HUD__

#define __HUD__

#include "player.h"

#include <SDL/SDL.h>

typedef struct HUD HUD;

HUD * new_hud(Player * player);

void hud_draw(HUD * display, SDL_Surface * canvas);

void free_hud(HUD * display);

#endif
