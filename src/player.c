#include "player.h"
#include "entity.h"
#include "zone.h"

struct Player
{
	char x;
	char y;
	Entity * body;
};

Player *
new_player()
{
	Player * me = (Player *) zone(sizeof(Player));
	me->body = load_entity("data/sprites/player/");
	return me;
}
