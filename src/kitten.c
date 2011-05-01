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
	Kitten * kitty = clone_entity(litter->mother);

	entity_set_position(kitty, x, y);

	return kitty;
}

void
free_kitten(Kitten * kitty)
{
	free_cloned_entity(kitty);
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
	entity_draw(kitty, canvas, cam);
}

void
register_kitten(Kitten * kitty, GSequence * others)
{
	register_entity(kitty, others);
}

void
kitten_move(Kitten * kitty, Player * me, Level world, TimeTracker * time, GSequence * others)
{
	float x, y;
	float px, py;
	float dx, dy;
	unsigned int dir;

	entity_position(kitty, &x, &y);
	entity_position(player_entity(me), &px, &py);

	if (can_see(world, x, y, px, py))
	{
		dir = look(x, y, px, py);

		if (dir == LEFT)
		{
			set_animation(kitty, "left");
		}
		else if (dir == RIGHT)
		{
			set_animation(kitty, "right");
		}
		else if (dir == UP)
		{
			set_animation(kitty, "up");
		}
		else if (dir == DOWN)
		{
			set_animation(kitty, "down");
		}
	}

	dx = px - x;
	dy = py - y;

	entity_set_direction(kitty, dx, dy);
	entity_move(kitty, world, time, others);
}
