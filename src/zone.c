#include <stdlib.h>
#include <stdio.h>

#include "zone.h"

void *
zone(size_t size)
{
	void * space = malloc(size);
	
	if (space)
	{
		return space;
	}
	else
	{
		fprintf(stderr, "OUT OF MEMORY!\n");
		exit(EXIT_FAILURE);
	}

}
