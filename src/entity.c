#include "entity.h"
#include "zone.h"
#include "sprite.h"
#include "directory.h"
#include "draw.h"

#include <SDL/SDL.h>
#include <glib.h>
#include <string.h>

struct Animation
{
	char count;
	SDL_Surface ** frames;
};

// An animation is an array of SDL_Surfaces
typedef struct Animation Animation;

struct Entity
{
	GTree * animations;
	char * current_animation;
	char current_frame;
};

void
draw_entity(Entity * thing, SDL_Surface * canvas, char x, char y)
{
	draw((SDL_Surface *) g_tree_lookup(thing->animations, thing->current_animation), canvas, x, y);
}

// Helper strcat function
char * zonecat(char * part, char * rest)
{
	char * buffer;
	buffer = (char *) zone(sizeof(char) * (strlen(part) + strlen(rest)));
	strcpy(buffer, part);
	return strcat(buffer, rest);
}

Animation *
load_animation(const char * path)
{
	char i;

	GArray * files;
	char * sprite_path;

	Animation * movie = (Animation *) zone(sizeof(Animation));

	files = directory_entries(path);

	movie->frames = (SDL_Surface **) zone(sizeof(SDL_Surface *) * files->len);
	movie->count = files->len;

	for (i = 0; i < files->len; i++)
	{
		sprite_path = zonecat((char *) path, g_array_index(files, char *, i));
		(movie->frames)[i] = load_sprite(sprite_path);
		free(sprite_path);
	}

	free_directory_entries(files);

	return movie;

}

gint
gstrcmp(const void * s1, const void * s2)
{
	return (gint) strcmp((char *) s1, (char *) s2);
}

Entity *
new_entity()
{
	Entity * thing = (Entity *) zone(sizeof(Entity));
	thing->animations = g_tree_new(&gstrcmp);
	thing->current_animation = (char *) zone(sizeof(char) * 100);
	thing->current_frame = 0;
	set_animation(thing, (char *) "default");
}

void
free_animation(Animation * movie)
{
	char i;

	for (i = 0; i < movie->count; i++)
	{
		SDL_FreeSurface((movie->frames)[i]);
	}

	free(movie->frames);

	free(movie);
}

gboolean
free_entity_animation(gpointer name, gpointer movie, gpointer vcrap)
{
	free_animation((Animation *) movie);
	free(name);
	return FALSE;
}

void
free_entity(Entity * thing)
{
	g_tree_foreach(thing->animations, &free_entity_animation, NULL);
	g_tree_destroy(thing->animations);
	free(thing->current_animation);
	free(thing);
}

void
add_animation(Entity * creature, char * name, Animation * action)
{
	g_tree_insert(creature->animations, name, action);
}

void
set_animation(Entity * thing, char * name)
{
	strcpy(thing->current_animation, name);
}

void
next_frame(Entity * thing)
{
	Animation * movie = (Animation *) g_tree_lookup(thing->animations, thing->current_animation);
	if (thing->current_frame == movie->count -1)
	{
		thing->current_frame = 0;
	}
	else
	{
		thing->current_frame++;
	}
}

Entity *
load_entity(const char * path)
{
	GArray * files;
	
	char * animation_name;

	char * animation_path;

	int i;

	Entity * thing = new_entity();

	files = directory_entries(path);

	for (i = 0; i < files->len; i++)
	{
		animation_name = g_array_index(files, char *, i);
		animation_path = zonecat((char *) path, animation_name);
		g_tree_insert(thing->animations, animation_name, load_animation(animation_path)); 
	}

	return thing;
}
