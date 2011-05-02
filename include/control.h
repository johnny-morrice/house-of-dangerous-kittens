#ifndef __CONTROL__

#define __CONTROL__

#include "input.h"

#include <glib.h>

typedef struct Control Control;

Control * new_control();

// Should the app quit?
gboolean running(Control * halter);

// Is the game still on?
gboolean playing(Control * halter);

// Stop the game (not the program)
void stop(Control * halter);

// The game is on
void play(Control * halter);

void check_exit(Control * halter, InputState * is);

#endif
