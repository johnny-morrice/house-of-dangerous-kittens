#include "entity.h"
#include "zone.h"
#include "sprite.h"
#include "directory.h"
#include "draw.h"
#include "timetrack.h"
#include "fatal.h"
#include "collide.h"

#include <SDL/SDL.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include <math.h>

#define ANIMATION_FPS 3

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
	EntitySet * set;
	unsigned int last_change;
	void (*interact)(gpointer);
	gpointer userdata;
	void (*destructor)(Entity *, gpointer);
};

// Allow the callbacks to operate on the thing
void
entity_interact(Entity * thing)
{
	(*(thing->interact))(entity_user_data(thing));
}


// Destroy the thing with the user's destructor
void
entity_destructor(Entity * thing)
{
	(*(thing->destructor))(thing, thing->userdata);
}

gpointer
entity_user_data(Entity * thing)
{
	return thing->userdata;
}

void
entity_set_speed(Entity * thing, float speed)
{
	thing->speed = speed;
}

gboolean
entity_set_direction(Entity * thing, float dx, float dy)
{
	float adx, ady;
	float mag = sqrt((dx * dx) + (dy * dy));

	if (mag > 0)
	{
		adx = dx / mag;
		ady = dy / mag;
	}
	else
	{
		adx = 0;
		adx = 0;
	}

	if (thing->dx != adx || thing->dy != ady)
	{
		thing->dx = adx;
		thing->dy = ady;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void
entity_set_position(Entity * thing, float x, float y)
{
	thing->x = x;
	thing->y = y;
}

struct Hit
{
	Entity * me;
	float targetx, targety;
	Entity * hit;
};

void
seq_collide(gpointer thp, gpointer hp)
{
	struct Hit * hit = (struct Hit *) hp;
	Entity * thing = thp;
	if (!(hit->hit || hit->me == thing))
	{
		if (collide(hit->targetx, hit->targety, thing->x, thing->y))
		{
			hit->hit = thing;
		}
	}
}

Entity *
collision(Entity * thing, float x, float y, EntitySet * others)
{
	struct Hit hit;
	hit.me = thing;
	hit.targetx = x;
	hit.targety = y;
	hit.hit = NULL; 

	g_slist_foreach(entity_list(others), &seq_collide, &hit);

	return hit.hit;
}

// Can you walk there?
gboolean
can_walk(float x, float y, Entity * thing, Level world, EntitySet * others)
{
	gboolean bounds = in_bounds(world, x, y);
	gboolean stuff = !collision(thing, x, y, others);

//	printf("(%f,%f) bounds? %d\n", x, y, bounds);
//	printf("(%f,%f) collision? %d\n", x, y, stuff);
	return bounds && stuff;
}


void
entity_move(Entity * thing, Level world, TimeTracker * time, EntitySet * others)
{
	float adjustdx, adjustdy;
	float x, y, nx, ny;

	adjustdx = thing->dx * thing->speed / fps(time);
	adjustdy = thing->dy * thing->speed / fps(time);

	if (! (isnan(adjustdx) || isnan(adjustdy) || (adjustdx == 0 && adjustdy == 0)))
	{
		x = thing->x;
		y = thing->y;

		nx = x + adjustdx;
		ny = y + adjustdy;

		if (can_walk(nx, ny, thing, world, others))
		{
			entity_set_position(thing, nx, ny);
		}
		else if (can_walk(x, ny, thing, world, others))
		{
			entity_set_position(thing, x, ny);
		}
		else if (can_walk(nx, y, thing, world, others))
		{
			entity_set_position(thing, nx, y);
		}
	}
}

void
entity_draw(Entity * thing, SDL_Surface * canvas, Camera * cam)
{
	unsigned int ticks;

	SDL_Surface * current;
	Animation * movie = (Animation *) g_tree_lookup(thing->animations, thing->current_animation);
	if (movie)
	{
		if (movie->count > 0)
		{
			current = movie->frames[thing->current_frame];
			draw(current, canvas, cam, thing->x, thing->y);

			ticks = SDL_GetTicks();

			// Check to see if we should switch to next frame
			if (((float) (ticks - thing->last_change) / 1000.0) > (float) (1.0 / ANIMATION_FPS))
			{
				thing->last_change = ticks;
				next_frame(thing);
			}
			
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
	buffer = (char *) zone(sizeof(char) * (strlen(part) + strlen(rest) + 1));
	strcpy(buffer, part);
	return strcat(buffer, rest);
}

// Compare two paths
// strcmp wasn't working here for some reason
gint
pathcmp(gconstpointer p1, gconstpointer p2)
{
	char * s1 = * (char * const *) p1;
	char * s2 = * (char * const *) p2;

	int cmp;

	if (s1[0] < s2[0])
	{
		cmp = -1;
	}
	else if (s1[0] > s2[0])
	{
		cmp = 1;
	}
	else
	{
		cmp = 0;
	}

	return (gint) cmp;
}

Animation *
load_animation(const char * path)
{
	unsigned int i;

	GArray * files;
	char * sprite_path;

	Animation * movie = (Animation *) zone(sizeof(Animation));

	printf("Loading animation %s\n", path);

	files = directory_entries(path);

	g_array_sort(files, &pathcmp);

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
allocate_entity(gpointer userdata,
		void (*interact)(gpointer),
		void (*destructor)(Entity *, gpointer))
{
	Entity * thing = (Entity *) zone(sizeof(Entity));
	thing->userdata = userdata;
	thing->interact = interact;
	thing->destructor = destructor;
	thing->current_animation = (char *) zone(sizeof(char) * 100);
	thing->current_frame = 0;
	thing->dx = 0;
	thing->dy = 0;
	thing->x = 0;
	thing->y = 0;
	thing->set = NULL;
	set_animation(thing, (char *) "default");
	return thing;

}

Entity *
new_entity(gpointer userdata,
		void (*interact)(gpointer),
		void (*destructor)(Entity *, gpointer))
{
	Entity * thing = allocate_entity(userdata, interact, destructor);
	thing->animations = g_tree_new(&gstrcmp);
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
free_cloned_entity(Entity * thing)
{
	free(thing->current_animation);
	free(thing);
}

void
entity_destroy(Entity * thing)
{
	if (thing->set)
	{
		remove_entity(thing->set, thing);
	}
	entity_destructor(thing);
}

void
free_entity(Entity * thing)
{
	g_tree_foreach(thing->animations, &free_entity_animation, NULL);
	g_tree_destroy(thing->animations);
	free_cloned_entity(thing);
}

void
add_animation(Entity * creature, char * name, Animation * action)
{
	g_tree_insert(creature->animations, name, action);
}

void
set_animation(Entity * thing, char * name)
{
	if (strcmp(thing->current_animation, name) != 0)
	{
		strcpy(thing->current_animation, name);
		thing->current_frame = 0;
		thing->last_change = SDL_GetTicks();
	}
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
load_entity(const char * path,
		gpointer user_data,
		void (*interact)(gpointer),
		void (*free_data)(Entity *, gpointer))
{
	GArray * files;
	
	char * animation_name;
	char * animation_file_name;

	char * animation_path;
	char * unterminated;

	unsigned int i;

	Entity * thing = new_entity(user_data, interact, free_data);

	printf("Loading entity %s\n", path);

	files = directory_entries(path);

	for (i = 0; i < files->len; i++)
	{
		animation_file_name = g_array_index(files, char *, i);
		animation_name = (char *) zone(sizeof(char) * strlen(animation_file_name) + 1);
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

// Centre the camera on an entity
void
entity_centre(Entity * me, Camera * cam)
{
	camera_centre(cam, me->x, me->y);
}

// Get the position of an entity
void
entity_position(Entity * me, float * x, float * y)
{
	*x = me->x;
	*y = me->y;
}

// Clone an entity
Entity *
clone_entity(Entity * thing)
{
	Entity * clone = allocate_entity(thing->userdata, thing->interact, thing->destructor);
	clone->animations = thing->animations;
	clone->speed = thing->speed;
	return clone;
}

// Note that this entity is in the set
void
entity_assign(Entity * thing, EntitySet * others)
{
	thing->set = others;
}


