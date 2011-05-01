#ifndef __INPUT__

#define __INPUT__

#include <SDL/SDL.h>
#include "draw.h"

typedef struct InputState InputState;

InputState * new_input_state();

void update_input(InputState * is);

// Is that key down?
char key_down(InputState * is, SDLKey key);

// Get the mouse position on the screen
void mouse_position(InputState * is, unsigned int * x, unsigned int * y);

// Did the user request quit?
char quit_happened(InputState * is);

void free_input(InputState * is);

#endif
