#include "player.h"
#include "entity.h"
#include "zone.h"
#include "input.h"
#include "draw.h"
#include "look.h"
#include "kitten.h"
#include "timetrack.h"
#include "audio.h"

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <glib.h>

#define PLAYER_ATTACK_FREQUENCY 9

#define PLAYER_PATH "data/sprites/player/"
#define FIRE_PATH "data/wav/fire.wav"

struct Player
{
	Entity * body;
	Camera * cam;
	InputState * is;
	EntitySet * others;
	Level world;
	Control * halter;
	unsigned int health;
	unsigned int score;
	Mix_Chunk * fire;
	Expirer * attack_timer;

};

unsigned int
player_score(Player * me)
{
	return me->score;
}

unsigned int
player_health(Player * me)
{
	return me->health;
}


void
player_hurt(Player * me)
{
	int health;

	health = me->health;

	if (health > 0)
	{
		me->health = health - 1;
	}
}

void
player_destructor(Entity * me, gpointer dat)
{
	Player * player = (Player *) dat;
	free_entity(me);
	free(player->attack_timer);
	Mix_FreeChunk(player->fire);
	free(player);
}

Player *
new_player(EntitySet * others, Camera * cam, InputState * is, Level world, Control * halter)
{
	Player * player = (Player *) zone(sizeof(Player));
	Entity * body = load_entity(PLAYER_PATH, player, &player_user_input_response, &player_destructor);

	player->body = body;
	player->others = others;
	player->cam = cam;
	player->is = is;
	player->world = world;
	player->health = 100;
	player->halter = halter;
	player->score = 0;
	player->fire = Mix_LoadWAV(FIRE_PATH);
	player->attack_timer = new_expirer(PLAYER_ATTACK_FREQUENCY);

	entity_set_speed(body, 3);
	entity_set_direction(body, 0, 0);
	register_entity(others, body);

	return player;
}

Entity *
player_entity(Player * me)
{
	return me->body;
}

// The player is alive
void
alive(Player * me)
{
	InputState * is;
	Camera * cam;
	EntitySet * others;
	Level world;

	unsigned int mousex;
	unsigned int mousey;

	float playerx, playery;

	float fake_lookx, fake_looky;
	float lookx, looky;
	unsigned int dir;

	float x, y;

	float dx = 0;
	float dy = 0;

	gboolean shoot;
	gboolean firing;

	Entity * target;

	is = me->is;
	cam = me->cam;
	others = me->others;
	world = me->world;

	firing = mouse_press(is);
	shoot = expired(me->attack_timer); 

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
	} else if (key_down(is, SDLK_d) || key_down(is, SDLK_RIGHT))
	{
		dx = 1;
	}

	if (key_down(is, SDLK_w) || key_down(is, SDLK_UP))
	{
		dy = -1;
	} else if (key_down(is, SDLK_s) || key_down(is, SDLK_DOWN))
	{
		dy = 1;
	}

	entity_set_direction(me->body, dx, dy);

	// Try to shoot a KITTY!
	if (firing)
	{
		if (shoot)
		{
			play_wav(me->fire);

			entity_position(me->body, &x, &y);

			if (can_see(world, x, y, lookx, looky))
			{
				target = collision(me->body, lookx, looky, others);



				if (target)
				{
					entity_destroy(target);
					me->score ++;
				}
			}
		}


		if (dx != 0 || dy != 0)
		{
			if (dir == LEFT)
			{
				set_animation(me->body, (char *) "shoot_walk_left");
			}
			else if (dir == RIGHT)
			{
				set_animation(me->body, (char *) "shoot_walk_right");
			}
			else if (dir == UP)
			{
				set_animation(me->body, (char *) "shoot_walk_up");
			}
			else if (dir == DOWN)
			{
				set_animation(me->body, (char *) "shoot_walk_down");
			}
		}
		else
		{
			if (dir == LEFT)
			{
				set_animation(me->body, (char *) "shoot_idle_left");
			}
			else if (dir == RIGHT)
			{
				set_animation(me->body, (char *) "shoot_idle_right");
			}
			else if (dir == UP)
			{
				set_animation(me->body, (char *) "shoot_idle_up");
			}
			else if (dir == DOWN)
			{
				set_animation(me->body, (char *) "shoot_idle_down");
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

// The player is dead
	void
dead(Player * me)
{

	InputState * is;

	is = me->is;

	set_animation(me->body, (char *) "dead");

	if (key_down(is, SDLK_RETURN))
	{
		stop(me->halter);
	}

}

// This is the player's callback where all its actions take place
	void
player_user_input_response(gpointer mep)
{	
	Player * me;

	me = (Player *) mep;

	if (me->health > 0)
	{
		alive(me);
	}
	else
	{
		dead(me);
	}
}

