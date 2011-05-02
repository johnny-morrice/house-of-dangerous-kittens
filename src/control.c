#include <SDL/SDL.h>
#include <glib.h>

#include "control.h"
#include "zone.h"
#include "input.h"

struct Control
{
	gboolean running;
	gboolean playing;
	gboolean paused_press;
	gboolean is_paused;
};

Control * new_control()
{
	Control * halter = (Control *) zone(sizeof(Control));
	halter->running = TRUE;
	halter->playing = TRUE;
	halter->paused_press = FALSE;
	halter->is_paused = FALSE;
	return halter;
}

gboolean
is_paused(Control * halter)
{
	return halter->is_paused;
}

void
check_pause(Control * halter, InputState * is)
{
	gboolean pressing;
	gboolean pressed;

	pressing = key_down(is, SDLK_p);
	pressed = halter->paused_press;

	if (pressing)
	{
		if (!pressed)
		{
			halter->is_paused = !halter->is_paused;
			halter->paused_press = TRUE;
		}
	}
	else
	{
		halter->paused_press = FALSE;
	}

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

