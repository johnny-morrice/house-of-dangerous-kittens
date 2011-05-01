#ifndef __ENTITY__

#define __ENTITY__

#include <SDL/SDL.h>
#include <glib.h>

#include "level.h"
#include "timetrack.h"
#include "draw.h"


// An entity is table of strings associated with animations
typedef struct Entity Entity; 

Entity * load_entity(const char * path);
void free_entity(Entity * thing);
void set_animation(Entity * creature, char * name);
void next_frame(Entity * creature);
void entity_draw(Entity * thing, SDL_Surface * canvas, Camera * cam);

void entity_move(Entity * thing, Level level, TimeTracker * time);
void entity_set_position(Entity * thing, float x, float y);
// Return true if there was a change of direction
gboolean entity_set_direction(Entity * thing, float dx, float dy);
void entity_set_speed(Entity * thing, float d);

void entity_position(Entity * thing, float * x, float * y);

// Centre camera on entity
void entity_centre(Entity * me, Camera * cam);

#endif
