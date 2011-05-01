#include "player.h"
#include "entity.h"
#include "zone.h"
#include "input.h"

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
player_fetch_direction(Player * me, InputState * is)
{
	float dx = 0;
	float dy = 0;
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

	if (entity_set_direction(me->body, dx, dy))
	{
		if (dx == -1)
		{
			set_animation(me->body, (char *) "walk_left_shotgun");
		}
		else if (dx == 1)
		{
			set_animation(me->body, (char *) "walk_right_shotgun");
		}
		else if (dy == -1)
		{
			set_animation(me->body, (char *) "walk_up_shotgun");
		}
		else if (dy == 1)
		{
			set_animation(me->body, (char *) "walk_down_shotgun");
		}
	}
}
