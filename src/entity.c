#include "entity.h"
#include "zone.h"
#include "sprite.h"
#include "directory.h"
#include "draw.h"
#include "timetrack.h"
#include "fatal.h"

#include <SDL/SDL.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include <math.h>

struct Animation
{
	unsigned int count;
	SDL_Surface ** frames;
};

// An animation is an array of SDL_Surfaces
typedef struct Animation Animation;

struct Entity
{
	GTree * animations;
	char * current_animation;
	unsigned int current_frame;
	float x;
	float y;
	float dx;
	float dy;
	float speed;

};

void
entity_set_speed(Entity * thing, float speed)
{
	thing->speed = speed;
}

void
entity_set_direction(Entity * thing, float dx, float dy)
{
	float mag = sqrt((dx * dx) + (dy * dy));
	if (mag > 0)
	{
		thing->dx = dx / mag;
		thing->dy = dy / mag;
	}
	else
	{
		thing->dx = 0;
		thing->dy = 0;
	}
}

void
entity_set_position(Entity * thing, float x, float y)
{
	thing->x = x;
	thing->y = y;
}

void
entity_move(Entity * thing, Level world, TimeTracker * time)
{
	float adjustdx, adjustdy;
	float x, y;

	adjustdx = thing->dx / fps(time);
	adjustdy = thing->dy / fps(time);

	printf("fps: %d\n", fps(time));

	if (! (isnan(adjustdx) || isnan(adjustdy)))
	{

		x = thing->x + adjustdx;
		y = thing->y + adjustdy;

		if (in_bounds(world, x, y))
		{
			entity_set_position(thing, x, y);
		}
	}
}

void
entity_draw(Entity * thing, SDL_Surface * canvas)
{
	SDL_Surface * current;
	Animation * movie = (Animation *) g_tree_lookup(thing->animations, thing->current_animation);
	if (movie)
	{
		if (movie->count > 0)
		{
			current = movie->frames[thing->current_frame];
			draw(current, canvas, thing->x, thing->y);
		}
		else
		{
			fprintf(stderr, "No frames for animation '%s'\n", thing->current_animation);
			die();
		}
	}
	else
	{
		fprintf(stderr, "Could not find animation '%s'\n", thing->current_animation);
		die();
	}
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
	unsigned int i;

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
	return thing;
}

void
free_animation(Animation * movie)
{
	unsigned int i;

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
	thing->current_frame = 0;
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
	char * animation_file_name;

	char * animation_path;
	char * unterminated;

	unsigned int i;

	Entity * thing = new_entity();

	files = directory_entries(path);

	for (i = 0; i < files->len; i++)
	{
		animation_file_name = g_array_index(files, char *, i);
		animation_name = (char *) zone(sizeof(char) * strlen(animation_file_name));
		strcpy(animation_name, animation_file_name);
		unterminated = zonecat((char *) path, animation_name);
		animation_path = zonecat(unterminated, (char *) "/");
		g_tree_insert(thing->animations, animation_name, load_animation(animation_path));
		free(unterminated);
		free(animation_path);
	}

	free_directory_entries(files);

	return thing;
}
