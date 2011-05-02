/* Copyright 2011 John Morrice
 *
 * Contact spoon@killersmurf.com
 *
 * This file is part of Dangerous Kittens.
 *
 * Dangerous Kittens is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dangerous Kittens is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dangerous Kittens.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "input.h"
#include "zone.h"

#include <SDL/SDL.h>
#include <glib.h>

struct InputState
{
	GSList * down;
	unsigned int mousex;
	unsigned int mousey;
	char quit_event;
	gboolean mouse_press;

};

InputState *
new_input_state()
{
	InputState * is;

	is = (InputState *) zone(sizeof(InputState));
	is->down = NULL;
	is->quit_event = 0;
	is->mouse_press = FALSE;
	is->mousex = 0;
	is->mousey = 0;
	return is;
}

void
free_input(InputState * is)
{
	g_slist_free(is->down);
	free(is);
}

char
quit_happened(InputState * is)
{
	return is->quit_event;
}

// Is this key down?
gboolean
key_down(InputState * is, SDLKey key)
{
	gpointer present;
	
	present = g_slist_find(is->down, GINT_TO_POINTER(key));
	// Convert from pointer to boolean
	if (present)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void
update_input(InputState * is)
{
	SDL_Event event;
	int another;

	another = SDL_PollEvent(&event);

	while (another)
	{
		if (event.type == SDL_QUIT)
		{
			is->quit_event = 1;
		}
		else if (event.type == SDL_KEYUP)
		{
			is->down = g_slist_remove(is->down, GINT_TO_POINTER(event.key.keysym.sym));
		}
		else if (event.type == SDL_KEYDOWN)
		{
			is->down = g_slist_prepend(is->down, GINT_TO_POINTER(event.key.keysym.sym));
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			is->mousex = event.motion.x;
			is->mousey = event.motion.y;
		}
		// There is a bug here where you can press both buttons and then release one and have the shooting stop.
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			is->mouse_press = TRUE;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			is->mouse_press = FALSE;
		}
		another = SDL_PollEvent(&event);
	}
}

void
mouse_position(InputState * is, unsigned int * x, unsigned int * y)
{
	*x = is->mousex;
	*y = is->mousey;
}

gboolean
mouse_press(InputState * is)
{
	return is->mouse_press;
}
