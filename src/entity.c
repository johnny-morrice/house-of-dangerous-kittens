#include "entity.h"
#include "zone.h"
#include "sprite.h"

#include <SDL/SDL.h>
#include <glib.h>
#include <string.h>

struct Animation
{
	char count;
	SDL_Surface ** frames;
}

struct Entity
{
	GTree * animations;
	char * current_animation;
	char current_frame;
};

char * zonecat(char * buffer, char * str)
{
	char * root_rel;
	root_rel = zone(sizeof(char) * (strlen(buffer) + strlen(part)));
	strcpy(root_rel, buffer);
	return strcat(root_rel, path);
}

void
draw_entity(Entity * thing, SDL_Surface * canvas, char x, char y)
{
	draw(g_tree_lookup(thing->animations, thing->current_animation), canvas, x, y);
}

	Animation *
load_animation(const char * path)
{
	GDir folder;
	char * file;

	GArray files;

	char i;

	Animation * movie = (Animation *) zone(sizeof(Animation));

	files = g_array_new(FALSE, FALSE, sizeof(char *));

	folder = g_dir_open(path);

	file = g_dir_read_name(folder);

	while (file)
	{
		g_array_append_val(files, file);
		file = g_dir_read_name(folder);
	}

	g_array_sort(files, &strcmp);

	movie->frames = (SDL_Surface **) zone(sizeof(SDL_Surface *) * files->len);
	movie->count = files->len;

	for (i = 0; i < files->len; i++)
	{
		file = g_array_index(files, char *, i);
		(movie->frames)[i] = load_sprite(file);
		free(file);
	}

	g_array_free(files, TRUE);
	return movie;

}

	Entity *
new_entity()
{
	Entity thing = (Entity *) zone(sizeof(Entity));
	thing->animations = g_tree_new(&strcmp);
	thing->current_animation = (char *) "default";
	thing->current_frame = 0;
}

	void
add_animation(Entity * creature, char * name, Animation * action)
{
	g_tree_insert(creature->animations, name, g_slist_reverse(action));
}

	void
set_animation(Entity * thing, char * name)
{
	thing->current_animation = name;
}

	void
next_frame(Entity * thing)
{
	Animation * movie = g_tree_lookup(thing->animations, thing->current_animation)
}
