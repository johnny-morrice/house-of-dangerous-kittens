#include "player.h"
#include "entity.h"
#include "zone.h"

struct Player
{
	Entity * body;
};

Player *
new_player()
{
	Player * me = (Player *) zone(sizeof(Player));
	Entity * body = load_entity("data/sprites/player/");
	body->speed = 1;
	body->dx = 0;
	body->dy = 0;
	me->body = body;
	return me;
}

