#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "array.h"

#include "bubblesort.h"
#include "quicksort.h"

typedef struct algorithm {
	char name[30];
	void (*function)(array_t*, void (*)(array_t*,int));
} algorithm_t;

const algorithm_t AVAILABLE_ALGOS[] = {
	{ "Bubble Sort", &bubblesort },
	{ "Quicksort", &quicksort },
	{ "", NULL }
};

#endif
