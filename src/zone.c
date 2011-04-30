#include <stdlib.h>
#include <stdio.h>

#include "zone.h"
#include "fatal.h"

void *
zone(size_t size)
{
	void * space = malloc(size);
	
	if (!space)
	{
		fatal("Out of memory\n");
	}

	return space;
}
