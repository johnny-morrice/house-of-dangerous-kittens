#include "fatal.h"

#include <stdio.h>
#include <stdlib.h>

void
fatal(const char * msg)
{
	fprintf(stderr, "FATAL ERROR:\n%s", msg);
	exit(EXIT_FAILURE);
}
