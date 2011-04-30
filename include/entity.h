#ifndef __ENTITY__

#define __ENTITY__

#include <SDL/SDL.h>
#include <glib.h>


// An entity is table of strings associated with animations
typedef struct Entity Entity; 

Entity * load_entity(const char * path);
void free_entity(Entity * thing);
void set_animation(Entity * creature, char * name);
void next_frame(Entity * creature, char * name);
void draw_entity(Entity * thing, SDL_Surface * canvas, char x, char y);

void entity_move(Entity * thing, Level level, TimeTracker * time);
void entity_set_position(Entity * thing, char x, char y);
void entity_set_direction(Entity * thing, char dx, char dy);

#endif
