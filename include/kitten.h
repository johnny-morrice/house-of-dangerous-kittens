#ifndef __KITTEN__

#define __KITTEN__

#include "level.h"
#include "player.h"
#include "draw.h"
#include "timetrack.h"

#include <SDL/SDL.h>

typedef struct KittenManager KittenManager;

typedef struct Kitten Kitten;

// Create a kitten
Kitten *
clone_kitten(KittenManager * litter, float x, float y);

// Load the kittens from the sprites
KittenManager *
load_kittens();

// Free a kitten
void
free_kitten(Kitten * kitty);

// Free the litter (must free kittens separately)
void
free_kittens(KittenManager * litter);

// Move the kitten toward the player
void
kitten_move(Kitten * kitty, Player * me, Level world, TimeTracker * time);

// Draw the kitten
void
kitten_draw(Kitten * kitty, SDL_Surface * canvas, Camera * cam);


#endif
