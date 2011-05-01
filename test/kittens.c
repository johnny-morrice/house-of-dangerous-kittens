#include <stdlib.h>
#include <SDL/SDL.h>

#include "entity.h"
#include "screen.h"
#include "input.h"
#include "control.h"
#include "player.h"
#include "timetrack.h"
#include "level.h"
#include "tiles.h"
#include "kitten.h"
#include "cursor.h"

int
main(int argc, char ** argv)
{
	char i, j;

	SDL_Surface * screen = init_sdl();
	SDL_Surface * cursor = load_cursor();
	InputState * is = new_input_state();
	Control * halter = new_control();
	Player * player = new_player();
	Entity * body = player_entity(player);
	Level level = new_level();
	TimeTracker * time = new_time_tracker();
	Camera * cam = new_camera();
	TileManager * tiles = load_tiles();
	KittenManager * litter = load_kittens();
	Kitten * kitten = clone_kitten(litter, 6, 6);

	GSequence * others = entity_sequence(); 
	register_kitten(kitten, others);
	register_entity(body, others);

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j ++)
		{
			level_set_square(level, tiles, i, j, square_carpet);
		}
	}

	entity_set_position(body, 5, 5);

	while (running(halter))
	{
		SDL_FillRect(screen, NULL, 0);
		update_input(is);

		entity_centre(body, cam);
		player_set_direction(player, is, cam);
		entity_move(body, level, time, others);

		kitten_move(kitten, player, level, time, others);

		level_draw(level, screen, cam);
		entity_draw(body, screen, cam);
		kitten_draw(kitten, screen, cam);

		draw_cursor(is, cursor, screen);


		SDL_Flip(screen);

		check_exit(halter, is);
		frame_done(time);
	}

	g_sequence_free(others);
	free(cam);
	free(halter);
	free_player(player);
	free_level(level);
	free_input(is);
	free_tiles(tiles);
	free_kittens(litter);
	free_kitten(kitten);

	SDL_Quit();

	return EXIT_SUCCESS;
}
