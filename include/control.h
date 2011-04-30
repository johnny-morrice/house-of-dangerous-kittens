#ifndef __CONTROL__

#define __CONTROL__

#include "input.h"

typedef struct Control Control;

Control * new_control();

char running(Control * halter);
void check_exit(Control * halter, InputState * is);

#endif
