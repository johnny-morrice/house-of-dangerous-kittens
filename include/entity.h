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

#ifndef __ENTITY__

#define __ENTITY__

#include <SDL/SDL.h>
#include <glib.h>

#include "level.h"
#include "timetrack.h"
#include "draw.h"

typedef struct Entity Entity; 

typedef struct EntitySet EntitySet;

Entity * load_entity(const char * path,
		gpointer userdata,
		void (*interact)(gpointer),
		void (*destructor)(Entity *, gpointer));

// Other entities should use this to get rid of an entity
void entity_destroy(Entity * thing);

// Call the destructor
void entity_destructor(Entity * thing);

// Call the interact callback
void entity_interact(Entity * thing);

void free_entity(Entity * thing);
void set_animation(Entity * creature, char * name);
void next_frame(Entity * creature);
void entity_draw(Entity * thing, SDL_Surface * canvas, Camera * cam);

void entity_move(Entity * thing, Level level, TimeTracker * time, EntitySet * others);
void entity_set_position(Entity * thing, float x, float y);
// Return true if there was a change of direction
gboolean entity_set_direction(Entity * thing, float dx, float dy);
void entity_set_speed(Entity * thing, float d);

void entity_position(Entity * thing, float * x, float * y);

// Write the direction into the pointers
void entity_get_direction(Entity * thing, float * dx, float * dy);


// Clone an entity
Entity * clone_entity(Entity * thing);
// Free a cloned entity
void free_cloned_entity(Entity * clone);

// Centre camera on entity
void entity_centre(Entity * me, Camera * cam);

// Assign to an entity set
void entity_assign(Entity * thing, EntitySet * set);

Entity * collision(Entity * thing, float x, float y, EntitySet * others);

gpointer entity_user_data(Entity * thing);

void entity_set_user_data(Entity * thing, gpointer userdata);

// Entity set functions

EntitySet * new_entity_set();

void free_entity_set(EntitySet * entities);

void entities_interact(EntitySet * entities);

void entities_move(EntitySet * entities, Level world, TimeTracker * time);

void entities_draw(EntitySet * entities, SDL_Surface * canvas, Camera * cam, gboolean ** seen);

void register_entity(EntitySet * entities, Entity * thing);

void remove_entity(EntitySet * entities, Entity * thing);

void each_entity(EntitySet * entities, void (*eachf)(Entity *));

GSList * entity_list(EntitySet * entities);

#endif
