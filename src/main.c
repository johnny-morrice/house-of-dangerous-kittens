#include <stdlib.h>
#include <SDL/SDL.h>

#include "audio.h"
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
	gboolean ** seen;

	float px, py;

	screen = init_sdl();
	init_audio();
	cursor = load_cursor();
	is = new_input_state();
	halter = new_control();
	cam = new_camera();
	
	time = new_time_tracker();

	tiles = load_tiles();

	seen = new_seen_grid();

	while (running(halter))
	{
		world = new_level();
		entities = new_entity_set();
		player = new_player(entities, cam, is, world, halter);
		display = new_hud(player, time);
		body = player_entity(player);

		entity_set_position(body, 0, 0);

		litter = load_kittens(body, world, time, entities);

		load_level(world, tiles, "data/level.txt");

		play(halter);

		while (running(halter) && playing(halter))
		{

			SDL_FillRect(screen, NULL, 0);

			update_input(is);

			entity_centre(body, cam);

			entities_interact(entities);

			entities_move(entities, world, time);

			entity_position(body, &px, &py);

			line_of_sight(world, seen, px, py);

			spawn_more_kittens(litter, seen);

			level_draw(world, screen, cam, seen);

			entities_draw(entities, screen, cam, seen);

			draw_cursor(is, cursor, screen);

			hud_draw(display, screen);

			SDL_Flip(screen);

			check_exit(halter, is);

			frame_done(time);

		}

		free_entity_set(entities);

		free_level(world);;
		free_hud(display);


		free_kittens(litter);
	}

	free_seen_grid(seen);

	free(cam);

	free_tiles(tiles);

	free(time);

	free(halter);

	free_input(is);

	close_audio();

	SDL_FreeSurface(cursor);

	shutdown_sdl();

	return EXIT_SUCCESS;
}
