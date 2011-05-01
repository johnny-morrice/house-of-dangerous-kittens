#include <stdlib.h>
#include <SDL/SDL.h>

#include "entity.h"
#include "screen.h"
#include "input.h"
#include "control.h"
#include "player.h"
#include "timetrack.h"
#include "level.h"

int
main(int argc, char ** argv)
{
	char i, j;

	SDL_Surface * screen = init_sdl();
	InputState * is = new_input_state();
	Control * halter = new_control();
	Player * player = new_player();
	Entity * body = player_entity(player);
	Level level = new_level();
	TimeTracker * time = new_time_tracker();
	Camera * cam = new_camera();

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j ++)
		{
			level_set_square(level, i, j, square_carpet);
		}
	}

	entity_set_position(body, 5, 5);

	while (running(halter))
	{
		SDL_FillRect(screen, NULL, 0);
		update_input(is);
		entity_centre(body, cam);
		player_fetch_direction(player, is);
		entity_move(body, level, time);
		level_draw(level, screen, cam);
		entity_draw(body, screen, cam);
		SDL_Flip(screen);

		check_exit(halter, is);
		frame_done(time);
	}

	free(cam);
	free(halter);
	free_player(player);
	free_level(level);
	free_input(is);

	SDL_Quit();

	return EXIT_SUCCESS;
}
