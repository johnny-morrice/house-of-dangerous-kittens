#include "fatal.h"

#include <stdio.h>
#include <stdlib.h>

void
die()
{
	fprintf(stderr, "Fatal error!\n");
	exit(EXIT_FAILURE);
}
