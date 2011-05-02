#include "kitten.h"
#include "entity.h"
#include "zone.h"
#include "look.h"
#include "timetrack.h"
#include "collide.h"
#include "player.h"
#include "audio.h"

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <glib.h>

#define ATTACK_FREQUENCY 20

#define CLAW_FREQUENCY 5

#define SPAWN_FREQUENCY 1

#define KITTEN_PATH "data/sprites/kitten/"
#define CLAW_PATH "data/wav/claw.wav"


struct KittenManager
{
	Entity * mother;
	Kitten * child;
	Expirer * spawn_timer;
	unsigned int kitten_count;
};

struct Kitten
{
	Entity * body;
	Entity * player;
	Level world;
	TimeTracker * time;
	EntitySet * others;
	Expirer * attack_timer;
	unsigned int * count_ptr;
	Mix_Chunk * claw;
	Expirer * claw_timer;
};

void
free_available(GArray * available)
{
	unsigned int i;

	for (i = 0; i < available->len; i++)
	{
		free(g_array_index(available, unsigned int *, i));
	}

	g_array_free(available, TRUE);
}

GArray *
available_squares(Level world, EntitySet * others)
{
	unsigned int i;
	unsigned int j;
	float fi, fj;
	GArray * available;

	unsigned int * coord;

	available = g_array_new(FALSE, FALSE, sizeof(unsigned int *)); 

	for (i = 0; i < level_width; i++)
	{
		for (j = 0; j < level_height; j++)
		{
			fi = (float) i;
			fj = (float) j;
			if (in_bounds(world, fi, fj) && NULL == collision(NULL, fi, fj, others))
			{
				coord = (unsigned int *) zone(sizeof(int) * 2);
				coord[0] = i;
				coord[1] = j;
				g_array_append_val(available, coord);
			}
		}
	}

	return available;
}

// Return random int between 0 and max
unsigned int
random_uint(unsigned int max)
{
	unsigned int choice;
	GRand * rng = g_rand_new();

	choice = g_rand_int_range(rng, 0, max);

	g_rand_free(rng);
	return choice;
}

void
spawn_kitten(KittenManager * litter, gboolean ** seen_grid)
{
	GArray * available;
	EntitySet * others;
	Level world;

	unsigned int ri;

	unsigned int * pending;
	unsigned int * chosen;

	others = litter->child->others;
	world = litter->child->world;

	available = available_squares(world, others);

	chosen = NULL;

	while (chosen == NULL)
	{
		ri = random_uint(available->len);
		pending = g_array_index(available, unsigned int *, ri);
		if (!seen_grid[pending[0]][pending[1]])
		{
			chosen = pending;
		}
	}

	clone_kitten(litter, (float) chosen[0], (float) chosen[1]);

	free_available(available);
}

void
spawn_more_kittens(KittenManager * litter, gboolean ** seen)
{
	unsigned int i;

	if (litter->kitten_count < 10 && expired(litter->spawn_timer))
	{
		for (i = 0; i < 10; i++)
		{
			spawn_kitten(litter, seen);
		}

	}
}

void
free_kitten(Kitten * kitty)
{
	free(kitty->claw_timer);
	free(kitty->attack_timer);
	free(kitty);
}

void
kitten_destructor(Entity * thing, gpointer kittyp)
{
	Kitten * kitty = (Kitten *) kittyp;

	free_cloned_entity(thing);

	*(kitty->count_ptr) = *(kitty->count_ptr) - 1;
	free_kitten(kitty);

}

KittenManager *
load_kittens(Entity * player, Level world, TimeTracker * time, EntitySet * others)
{
	KittenManager * litter = (KittenManager *) zone(sizeof(KittenManager));

	Kitten * kitty = (Kitten *) zone(sizeof(Kitten));

	Entity * mother = load_entity(KITTEN_PATH, kitty, &kitten_move, &kitten_destructor);

	kitty->body = mother;
	kitty->player = player;
	kitty->world = world;
	kitty->time = time;
	kitty->others = others;
	kitty->count_ptr = &litter->kitten_count;
	kitty->claw = Mix_LoadWAV(CLAW_PATH);

	litter->mother = mother;
	litter->child = kitty;
	litter->kitten_count = 0;
	litter->spawn_timer = new_expirer(SPAWN_FREQUENCY);

	entity_set_speed(mother, 6);

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
	kitty->attack_timer = new_expirer(ATTACK_FREQUENCY);
	kitty->claw_timer = new_expirer(CLAW_FREQUENCY);
	kitty->claw = mam->claw;
	kitty->count_ptr = &(litter->kitten_count);

	litter->kitten_count ++;

	entity_set_user_data(body, kitty);

	entity_set_position(body, x, y);

	register_entity(mam->others, body);

	return body;
}

void
free_kittens(KittenManager * litter)
{
	free_entity(litter->mother);
	Mix_FreeChunk(litter->child->claw);
	free(litter->child);
	free(litter);
}

void
kitten_draw(Kitten * kitty, SDL_Surface * canvas, Camera * cam)
{
	entity_draw(kitty->body, canvas, cam);
}

// This is the kitten's callback,
// all its actions take place here
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
	}

	entity_get_direction(body, &dx, &dy);

	if (collision(body, x + dx, y + dy, others) == player)
	{
		if (expired(kitty->claw_timer))
		{
			play_wav(kitty->claw);
		}

		if (expired(kitty->attack_timer))
		{
			dude = entity_user_data(player);
			player_hurt(dude);
		}
		if (dir == LEFT)
		{
			set_animation(body, "attack_left");
		}
		else if (dir == RIGHT)
		{
			set_animation(body, "attack_right");
		}
		else if (dir == UP)
		{
			set_animation(body, "attack_up");
		}
		else if (dir == DOWN)
		{
			set_animation(body, "attack_down");
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
