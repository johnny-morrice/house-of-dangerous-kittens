#include "entity.h"
#include "zone.h"

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
};

void
entity_drawf(gpointer entityp, gpointer drawp)
{
	struct DrawData * drawdat = (struct DrawData *) drawp;
	Entity * thing = (Entity *) entityp;
	entity_draw(thing, drawdat->canvas, drawdat->cam);
}

void
entities_draw(EntitySet * entities, SDL_Surface * canvas, Camera * cam)
{
	struct DrawData drawdat;
	drawdat.canvas = canvas;
	drawdat.cam = cam;
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
	entities->members = g_slist_remove(entities->members, thing);
}

GSList *
entity_list(EntitySet * entities)
{
	return entities->members;
}
