#include "player.h"
#include "entity.h"
#include "zone.h"
#include "input.h"
#include "draw.h"
#include "look.h"

#include <SDL/SDL.h>

struct Player
{
	Entity * body;
};

Player *
new_player()
{
	Player * me = (Player *) zone(sizeof(Player));
	Entity * body = load_entity("data/sprites/player/");
	entity_set_speed(body, 2);
	entity_set_direction(body, 0, 0);
	me->body = body;
	return me;
}

void
free_player(Player * me)
{
	free_entity(me->body);
	free(me);
}

Entity *
player_entity(Player * me)
{
	return me->body;
}

void
player_user_input_response(Player * me, InputState * is, Camera * cam)
{	
	unsigned int mousex;
	unsigned int mousey;

	float playerx, playery;

	float fake_lookx, fake_looky;
	float lookx, looky;
	unsigned int dir;

	float dx = 0;
	float dy = 0;

	gboolean shoot;

	shoot = mouse_press(is); 

	// Get the mouse position
	mouse_position(is, &mousex, &mousey);

	// Get the mouse position with regards to the level.
	camera_inverse_transform(cam, mousex, mousey, &fake_lookx, &fake_looky);
	lookx = fake_lookx / square_size;
	looky = fake_looky / square_size;

	entity_position(me->body, &playerx, &playery);

	dir = look(playerx, playery, lookx, looky);

	// Set the direction of the player with regards to key presses
	if (key_down(is, SDLK_a) || key_down(is, SDLK_LEFT))
	{
		dx = -1;
	}

	if (key_down(is, SDLK_d) || key_down(is, SDLK_RIGHT))
	{
		dx = 1;
	}

	if (key_down(is, SDLK_w) || key_down(is, SDLK_UP))
	{
		dy = -1;
	}

	if (key_down(is, SDLK_s) || key_down(is, SDLK_DOWN))
	{
		dy = 1;
	}

	entity_set_direction(me->body, dx, dy);

	if (shoot)
	{

		if (dx != 0 || dy != 0)
		{
			if (dir == LEFT)
			{
				set_animation(me->body, (char *) "walk_left_shoot");
			}
			else if (dir == RIGHT)
			{
				set_animation(me->body, (char *) "walk_right_shoot");
			}
			else if (dir == UP)
			{
				set_animation(me->body, (char *) "walk_up_shoot");
			}
			else if (dir == DOWN)
			{
				set_animation(me->body, (char *) "walk_down_shoot");
			}
		}
		else
		{
			if (dir == LEFT)
			{
				set_animation(me->body, (char *) "idle_left_shoot");
			}
			else if (dir == RIGHT)
			{
				set_animation(me->body, (char *) "idle_right_shoot");
			}
			else if (dir == UP)
			{
				set_animation(me->body, (char *) "idle_up_shoot");
			}
			else if (dir == DOWN)
			{
				set_animation(me->body, (char *) "idle_down_shoot");
			}

		}
	}
	else
	{
		if (dx != 0 || dy != 0)
		{
			if (dir == LEFT)
			{
				set_animation(me->body, (char *) "walk_left");
			}
			else if (dir == RIGHT)
			{
				set_animation(me->body, (char *) "walk_right");
			}
			else if (dir == UP)
			{
				set_animation(me->body, (char *) "walk_up");
			}
			else if (dir == DOWN)
			{
				set_animation(me->body, (char *) "walk_down");
			}
		}
		else
		{
			if (dir == LEFT)
			{
				set_animation(me->body, (char *) "idle_left");
			}
			else if (dir == RIGHT)
			{
				set_animation(me->body, (char *) "idle_right");
			}
			else if (dir == UP)
			{
				set_animation(me->body, (char *) "idle_up");
			}
			else if (dir == DOWN)
			{
				set_animation(me->body, (char *) "idle_down");
			}

		}

	}

}
