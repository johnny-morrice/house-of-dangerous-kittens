#include "kitten.h"
#include "entity.h"
#include "zone.h"
#include "look.h"
#include "timetrack.h"
#include "collide.h"
#include "player.h"

#include <SDL/SDL.h>
#include <glib.h>

struct KittenManager
{
	Entity * mother;
	Kitten * child;
};

struct Kitten
{
	Entity * body;
	Entity * player;
	Level world;
	TimeTracker * time;
	EntitySet * others;

};

void
kitten_destructor(Entity * thing, gpointer kittyp)
{
	free_cloned_entity(thing);
}

KittenManager *
load_kittens(Entity * player, Level world, TimeTracker * time, EntitySet * others)
{
	KittenManager * litter = (KittenManager *) zone(sizeof(KittenManager));

	Kitten * kitty = (Kitten *) zone(sizeof(Kitten));

	Entity * mother = load_entity("data/sprites/kitten/", kitty, &kitten_move, &kitten_destructor);

	kitty->body = mother;
	kitty->player = player;
	kitty->world = world;
	kitty->time = time;
	kitty->others = others;

	litter->mother = mother;
	litter->child = kitty;

	entity_set_speed(mother, 4);

	return litter;
}

Entity *
clone_kitten(KittenManager * litter, float x, float y)
{
	Entity * body = clone_entity(litter->mother);

	Kitten * mam = (Kitten *) entity_user_data(body);
	Kitten * kitty = (Kitten *) zone(sizeof(Kitten));

	kitty->player = mam->player;
	kitty->world = mam->world;
	kitty->time = mam->time;
	kitty->others = mam->others;
	kitty->body = body;

	entity_set_user_data(body, kitty);

	entity_set_position(body, x, y);

	return body;
}

void
free_kittens(KittenManager * litter)
{
	free_entity(litter->mother);
	free(litter->child);
	free(litter);
}

void
kitten_draw(Kitten * kitty, SDL_Surface * canvas, Camera * cam)
{
	entity_draw(kitty->body, canvas, cam);
}

void
kitten_move(gpointer kittyp)
{
	Kitten * kitty;
	Entity * player;
	Level world;
	TimeTracker * time;
	EntitySet * others;

	float x, y;
	float px, py;
	float dx, dy;
	unsigned int dir;
	Entity * body;

	Player * dude;

	kitty = (Kitten *) kittyp;
	player = kitty->player;
	world = kitty->world;
	time = kitty->time;
	others = kitty->others;
	body = kitty->body;

	entity_position(body, &x, &y);
	entity_position(player, &px, &py);

	dir = look(x, y, px, py);

	if (can_see(world, x, y, px, py))
	{
		
		dx = px - x;
		dy = py - y;

		entity_set_direction(body, dx, dy);
		entity_move(body, world, time, others);

		entity_get_direction(body, &dx, &dy);

		if (collision(body, x + dx, y + dy, others) == player)
		{
			dude = entity_user_data(player);
			player_hurt(dude);
		}
	}
	else if (dir == LEFT)
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
