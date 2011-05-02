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
#include "hud.h"
#include "look.h"

int
main(int argc, char ** argv)
{
	unsigned int i;

	SDL_Surface * screen; 
	SDL_Surface * cursor;
	InputState * is;
	Control * halter;
	Camera * cam;
	TimeTracker * time;
	Level world;
	EntitySet * entities;
	Player * player;
	HUD * display;
	Entity * body;
	TileManager * tiles;
	KittenManager * litter;
	Entity * kitten;
	GSList * seen;

	float px, py;

	screen = init_sdl();
	cursor = load_cursor();
	is = new_input_state();
	halter = new_control();
	cam = new_camera();
	
	time = new_time_tracker();

	tiles = load_tiles();

	while (running(halter))
	{
		world = new_level();
		entities = new_entity_set();
		player = new_player(entities, cam, is, world, halter);
		display = new_hud(player, time);
		body = player_entity(player);

		entity_set_position(body, 4, 3);

		litter = load_kittens(body, world, time, entities);

		kitten = clone_kitten(litter, 0, 3);
		register_entity(entities, kitten);

		for (i = 0; i < 4; i++)
		{
			level_set_square(world, tiles, 0, i, square_carpet);
			level_set_square(world, tiles, 1, i, square_carpet);
		}

		for (i = 0; i < 6; i++)
		{
			level_set_square(world, tiles, i, 0, square_carpet);
			level_set_square(world, tiles, i, 1, square_carpet);
		}

		for (i = 0; i < 4; i++)
		{
			level_set_square(world, tiles, 4, i, square_carpet);
			level_set_square(world, tiles, 5, i, square_carpet);
		}

		play(halter);

		while (running(halter) && playing(halter))
		{
			SDL_FillRect(screen, NULL, 0);

			update_input(is);

			entity_centre(body, cam);

			entities_interact(entities);

			entities_move(entities, world, time);

			entity_position(body, &px, &py);

			seen = line_of_sight(world, px, py);

			level_draw(world, screen, cam, seen);

			entities_draw(entities, screen, cam, seen);

			draw_cursor(is, cursor, screen);

			hud_draw(display, screen);

			SDL_Flip(screen);

			check_exit(halter, is);

			frame_done(time);

			free_seen(seen);
		}

		free_entity_set(entities);

		free_level(world);;
		free_hud(display);


		free_kittens(litter);
	}

	free(cam);

	free_tiles(tiles);

	free(time);

	free(halter);

	free_input(is);

	SDL_FreeSurface(cursor);

	SDL_Quit();

	return EXIT_SUCCESS;
}
