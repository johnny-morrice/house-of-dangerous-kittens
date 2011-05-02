#ifndef __HUD__

#define __HUD__

#include <SDL/SDL.h>

typedef struct HUD HUD;

HUD * new_hud();

void hud_draw(HUD * display, SDL_Surface * canvas);

void free_hud(HUD * display);

#endif
