#include "fatal.h"

#include <stdio.h>
#include <stdlib.h>

void
die()
{
	fprintf(stderr, "DIE DIE DIE DIE DIE\n");
	exit(EXIT_FAILURE);
}
