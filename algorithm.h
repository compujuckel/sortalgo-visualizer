#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "bubblesort.h"
#include "quicksort.h"

typedef struct algorithm {
	char name[30];
	void (*function)(int*, int, void (*)(int*,int));
} algorithm_t;

const algorithm_t AVAILABLE_ALGOS[] = {
	{ "Bubble Sort", &bubblesort },
	{ "Quicksort", &quicksort }
};

#endif
