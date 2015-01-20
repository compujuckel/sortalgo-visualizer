#include "util.h"

#include <stdio.h>
#include <stdlib.h>

void exit_with_error(char* message) {
	fprintf(stderr, "Error: %s", message);
	exit(EXIT_FAILURE);
}
