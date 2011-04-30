#include <stdlib.h>
#include <SDL/SDL.h>

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
	Level level = new_level();
	TimeTracker * time = new_time_tracker();

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j ++)
		{
			level_set_square(level, i, j, carpet);
		}
	}

	player_set_position(player, 5, 5);

	while (running(halter))
	{
		update_input(is);
		player_fetch_direction(player, is);
		player_move(player, level, time);
		level_draw(level, screen);
		player_draw(player, screen);
		SDL_Flip(screen);

		check_exit(halter, is);
		frame_done(time);
	}

	free(halter);
	free_player(player);
	free_level(level);
	free_input(is);

	SDL_Quit();

	return EXIT_SUCCESS;
}
