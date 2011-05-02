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

#include "directory.h"
#include "zone.h"
#include "fatal.h"

#include <string.h>
#include <glib.h>
#include <stdio.h>

GArray *
directory_entries(const char * path)
{
	GDir * folder;
	const gchar * temp;
	char * file;

	GArray * files;

	GError * error = NULL;

	files = g_array_new(FALSE, FALSE, sizeof(char *));

	folder = g_dir_open(path, 0, &error);

	if (!folder)
	{
		fprintf(stderr, "Could not find directory: '%s'\n", path);
		die();
	}

	temp = g_dir_read_name(folder);

	while (temp)
	{
		file = (char *) zone(sizeof(char) * strlen(temp) + 1);
		strcpy(file, temp);
		g_array_append_val(files, file);
		temp = g_dir_read_name(folder);
	}

	g_dir_close(folder);

	return files;
}

void
free_directory_entries(GArray * files)
{
	unsigned int i;

	for (i = 0; i < files->len; i ++)
	{
		free(g_array_index(files, char *, i));
	}

	g_array_free(files, TRUE);
}
