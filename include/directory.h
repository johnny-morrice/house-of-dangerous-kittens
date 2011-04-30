#ifndef __DIRECTORY__

#define __DIRECTORY__

#include <glib.h>

// Return each member of this directory as an array
GArray *
directory_entries(const char * path);

void
free_directory_entries(GArray * files);

#endif
