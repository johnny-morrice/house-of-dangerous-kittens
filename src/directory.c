#include "directory.h"
#include "zone.h"

#include <string.h>
#include <glib.h>

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

	temp = g_dir_read_name(folder);

	while (temp)
	{
		temp = g_dir_read_name(folder);
		file = (char *) zone(sizeof(char) * strlen(temp));
		strcpy(file, temp);
		g_array_append_val(files, file);

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
