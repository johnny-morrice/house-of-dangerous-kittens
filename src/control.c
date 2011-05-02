#include <SDL/SDL.h>
#include <glib.h>

#include "control.h"
#include "zone.h"
#include "input.h"

struct Control
{
	gboolean running;
	gboolean playing;
};

Control * new_control()
{
	Control * halter = (Control *) zone(sizeof(Control));
	halter->running = TRUE;
	halter->playing = TRUE;
	return halter;
}

gboolean
running(Control * halter)
{
	return halter->running;
}

gboolean
playing(Control * halter)
{
	return halter->playing;
}

void
stop(Control * halter)
{
	halter->playing = FALSE;
}

void
play(Control * halter)
{
	halter->playing = TRUE;
}

void
check_exit(Control * halter, InputState * is)
{
	if (key_down(is, SDLK_ESCAPE) || quit_happened(is))
	{
		halter->running = FALSE;
	}
}

