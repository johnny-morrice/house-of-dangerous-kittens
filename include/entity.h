#ifndef __ENTITY__

#define __ENTITY__

#include <SDL/SDL.h>
#include <glib.h>

// An animation is an array of SDL_Surfaces
typedef struct Animation Animation;

// An entity is table of strings associated with animations
typedef struct Entity Entity; 

// Load an animation from a directory
Animation * load_animation(const char * path);

Entity * new_entity();
void add_animation(Entity * creature, char * name, Animation * action);
void set_animation(Entity * creature, char * name);
void next_frame(Entity * creature, char * name);


#endif
