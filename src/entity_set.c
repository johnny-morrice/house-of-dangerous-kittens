#include "entity.h"
#include "zone.h"
#include "collide.h"

#include <glib.h>
#include <SDL/SDL.h>

struct EntitySet
{
	GSList * members;
};

typedef void (*iterfunc)(Entity *);

EntitySet *
new_entity_set()
{
	EntitySet * entities;
	entities = (EntitySet *) zone(sizeof(EntitySet));
	entities->members = NULL;
	return entities;
}

void
runnerf(gpointer entityp, gpointer func)
{
	iterfunc eachf;
	eachf = (iterfunc) func;
	(*eachf)((Entity *) entityp);
}

void
each_entity(EntitySet * entities, void (*eachf)(Entity *))
{
	g_slist_foreach(entities->members, &runnerf, eachf);
}

void
free_entity_set(EntitySet * entities)
{
	each_entity(entities, &entity_destructor);
	g_slist_free(entities->members);
	free(entities);
}

void
entities_interact(EntitySet * entities)
{
	each_entity(entities, &entity_interact);
}

struct MoveData
{
	Level level;
	TimeTracker * time;
	EntitySet * entities;
};

void entity_movef(gpointer entityp, gpointer datp)
{
	struct MoveData * movdat = (struct MoveData *) datp;
	Entity * thing = (Entity *) entityp;
	entity_move(thing, movdat->level, movdat->time, movdat->entities);
}

void
entities_move(EntitySet * entities, Level level, TimeTracker * time)
{
	struct MoveData movdat;
	movdat.entities = entities;
	movdat.level = level;
	movdat.time = time;
	g_slist_foreach(entities->members, &entity_movef, &movdat);
}

struct DrawData
{
	SDL_Surface * canvas;
	Camera * cam;
	GSList * seen;
};

struct SeeCheck
{
	Entity * thing;
	gboolean can;
};

void
see_checkf(gpointer coordp, gpointer seep)
{
	struct SeeCheck * see_check = (struct SeeCheck *) seep;
	float * coord = (float *) coordp;
	float x, y;

	entity_position(see_check->thing, &x, &y);

	if (!see_check->can)
	{
		see_check->can = collide(coord[0], coord[1], x, y);
	}
}

void
entity_drawf(gpointer entityp, gpointer drawp)
{
	struct SeeCheck see_check;
	struct DrawData * drawdat = (struct DrawData *) drawp;
	Entity * thing = (Entity *) entityp;

	see_check.thing = thing;
	see_check.can = FALSE;

	g_slist_foreach(drawdat->seen, &see_checkf, &see_check);

	if (see_check.can)
	{
		entity_draw(thing, drawdat->canvas, drawdat->cam);
	}
}

void
entities_draw(EntitySet * entities, SDL_Surface * canvas, Camera * cam, GSList * seen)
{
	struct DrawData drawdat;
	drawdat.canvas = canvas;
	drawdat.cam = cam;
	drawdat.seen = seen;
	g_slist_foreach(entities->members, &entity_drawf, &drawdat);
}

void
register_entity(EntitySet * entities, Entity * thing)
{
	entities->members = g_slist_prepend(entities->members, thing);
	entity_assign(thing, entities);
}

void
remove_entity(EntitySet * entities, Entity * thing)
{
	entities->members = g_slist_remove_all(entities->members, thing);
}

GSList *
entity_list(EntitySet * entities)
{
	return entities->members;
}
