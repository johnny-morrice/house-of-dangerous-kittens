/* Copyright 2011 John Morrice
 *
 * Contact spoon@killersmurf.com
 *
 * This file is part of Dangerous Kittens.
 *
 * Dangerous Kittens is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dangerous Kittens is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dangerous Kittens.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "entity.h"
#include "zone.h"
#include "collide.h"

#include <glib.h>
#include <SDL/SDL.h>
#include "math.h"

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
	gboolean ** seen;
};

void
entity_drawf(gpointer entityp, gpointer drawp)
{
	float x, y;

	unsigned int i;
	unsigned int j;

	struct DrawData * drawdat = (struct DrawData *) drawp;
	Entity * thing = (Entity *) entityp;

	entity_position(thing, &x, &y);

	i = floor(x);
	j = floor(y);

	if ((drawdat->seen)[i][j])
	{
		entity_draw(thing, drawdat->canvas, drawdat->cam);
	}
}

void
entities_draw(EntitySet * entities, SDL_Surface * canvas, Camera * cam, gboolean ** seen)
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
