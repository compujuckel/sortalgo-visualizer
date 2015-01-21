#include "timer.h"
#include "util.h"

#include <sys/time.h>
#include <stdlib.h>

static struct timeval start;

void timer_start(void) {
	gettimeofday(&start, NULL);
}

double timer_status(void) {
	struct timeval end;
	gettimeofday(&end, NULL);
	struct timeval result;
	timersub(&end, &start, &result);
	return (double)result.tv_sec + (double)result.tv_usec / 1000000;
}
