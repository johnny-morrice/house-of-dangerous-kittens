#include "kitten.h"
#include "player.h"
#include "entity.h"
#include "zone.h"
#include "look.h"
#include "timetrack.h"

#include <SDL/SDL.h>
#include <glib.h>

struct KittenManager
{
	Entity * mother;
};

struct Kitten
{
	Entity * body;
};

KittenManager *
load_kittens()
{
	KittenManager * litter = (KittenManager *) zone(sizeof(KittenManager));
	Entity * mother = load_entity("data/sprites/kitten/");
	litter->mother = mother;

	entity_set_speed(mother, 4);

	return litter;
}

Kitten *
clone_kitten(KittenManager * litter, float x, float y)
{
	Kitten * kitty = (Kitten *) zone(sizeof(Kitten));
	Entity * body = clone_entity(litter->mother);
	kitty->body = body;

	entity_set_position(body, x, y);

	return kitty;
}

void
free_kitten(Kitten * kitty)
{
	free_cloned_entity(kitty->body);
	free(kitty);
}

void
free_kittens(KittenManager * litter)
{
	free_entity(litter->mother);
	free(litter);
}

void
kitten_draw(Kitten * kitty, SDL_Surface * canvas, Camera * cam)
{
	entity_draw(kitty->body, canvas, cam);
}

void
register_kitten(Kitten * kitty, GSequence * others)
{
	register_entity(kitty->body, others);
}

void
kitten_move(Kitten * kitty, Player * me, Level world, TimeTracker * time, GSequence * others)
{
	float x, y;
	float px, py;
	float dx, dy;
	unsigned int dir;
	Entity * body;

	body = kitty->body;

	entity_position(body, &x, &y);
	entity_position(player_entity(me), &px, &py);

	if (can_see(world, x, y, px, py))
	{
		dir = look(x, y, px, py);

		if (dir == LEFT)
		{
			set_animation(body, "left");
		}
		else if (dir == RIGHT)
		{
			set_animation(body, "right");
		}
		else if (dir == UP)
		{
			set_animation(body, "up");
		}
		else if (dir == DOWN)
		{
			set_animation(body, "down");
		}
	}

	dx = px - x;
	dy = py - y;

	entity_set_direction(body, dx, dy);
	entity_move(body, world, time, others);
}
