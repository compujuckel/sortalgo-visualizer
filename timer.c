#include "timer.h"
#include "util.h"

#include <time.h>
#include <stdlib.h>

static clock_t start = 0;

void timer_start(void) {
	start = clock();
}

timeinfo_t* timer_stop(void) {
	clock_t end = clock();
	
	timeinfo_t* t = malloc(sizeof(timeinfo_t));
	if(t == NULL)
		exit_with_error("malloc failed");
	t->clocks = end - start;
	t->seconds = ((double) (end - start)) / CLOCKS_PER_SEC;

	start = 0;
	return t;
}
