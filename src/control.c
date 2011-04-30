#include <SDL/SDL.h>

#include "control.h"
#include "zone.h"
#include "input.h"

struct Control
{
	char running;
};

Control * new_control()
{
	Control * halter = (Control *) zone(sizeof(Control));
	halter->running = 1;
	return halter;
}

char running(Control * halter)
{
	return halter->running;
}

void check_exit(Control * halter, InputState * is)
{
	if (key_down(is, SDLK_ESCAPE) || quit_happened(is))
	{
		halter->running = 0;
	}
}

