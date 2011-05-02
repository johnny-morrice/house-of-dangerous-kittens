#ifndef __KITTEN__

#define __KITTEN__

#include "level.h"
#include "player.h"
#include "draw.h"
#include "timetrack.h"

#include <glib.h>
#include <SDL/SDL.h>

typedef struct KittenManager KittenManager;

typedef struct Kitten Kitten;

// Spawn more kittens, somewhere in the level that we can't see!
void spawn_more_kittens(KittenManager * litter, gboolean ** seen);

// Create a kitten
Entity *
clone_kitten(KittenManager * litter, float x, float y);

// Load the kittens from the sprites
KittenManager *
load_kittens();

// Free the litter
void
free_kittens(KittenManager * litter);

// Move the kitten toward the player
void
kitten_move(gpointer kitty);

#endif
