#ifndef TIME_H
#define TIME_H

#include <time.h>

typedef struct timeinfo {
	clock_t clocks;
	double seconds;
} timeinfo_t;

void timer_start(void);
timeinfo_t* timer_stop(void);

#endif
