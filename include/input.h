#ifndef __INPUT__

#define __INPUT__

#include <SDL/SDL.h>

typedef struct InputState InputState;

InputState * new_input_state();

void update_input(InputState * is);

// Is that key down?
char key_down(InputState * is, SDLKey key);

// Did the user request quit?
char quit_happened(InputState * is);

void free_input(InputState * is);

#endif
