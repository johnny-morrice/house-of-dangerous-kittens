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
char
key_down(InputState * is, SDLKey key)
{
	gpointer present;
	
	present = g_slist_find(is->down, GINT_TO_POINTER(key));
	if (present)
	{
		return GPOINTER_TO_INT(present);
	}
	else
	{
		return 0;
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
			printf("Key up: %d\n", event.key.keysym.sym);
		}
		else if (event.type == SDL_KEYDOWN)
		{
			is->down = g_slist_prepend(is->down, GINT_TO_POINTER(event.key.keysym.sym));
			printf("Key down: %d\n", event.key.keysym.sym);
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
