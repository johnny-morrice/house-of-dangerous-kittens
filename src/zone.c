#include <stdio.h>

#include "zone.h"
#include "fatal.h"

void *
zone(size_t size)
{
	void * space = malloc(size);
	
	if (!space)
	{
		fprintf(stderr, "Out of memory\n");
		die();
	}

	return space;
}
