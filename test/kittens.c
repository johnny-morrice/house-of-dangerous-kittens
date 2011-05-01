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
	Camera * cam = new_camera();

	EntitySet * entities = new_entity_set();

	Player * player = new_player(entities, cam, is);
	Entity * body = player_entity(player);
	Level world = new_level();
	TimeTracker * time = new_time_tracker();
	TileManager * tiles = load_tiles();
	KittenManager * litter = load_kittens(body, world, time, entities);
	Entity * kitten = clone_kitten(litter, 6, 6);

	register_entity(entities, kitten);

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j ++)
		{
			level_set_square(world, tiles, i, j, square_carpet);
		}
	}

	entity_set_position(body, 5, 5);

	while (running(halter))
	{
		SDL_FillRect(screen, NULL, 0);

		update_input(is);

		entity_centre(body, cam);

		entities_interact(entities);

		entities_move(entities, world, time);

		level_draw(world, screen, cam);

		entities_draw(entities, screen, cam);

		draw_cursor(is, cursor, screen);

		SDL_Flip(screen);

		check_exit(halter, is);

		frame_done(time);
	}

	free_entity_set(entities);
	free(cam);
	free(halter);
	free_level(world);
	free_input(is);
	free_tiles(tiles);
	free_kittens(litter);

	SDL_Quit();

	return EXIT_SUCCESS;
}
