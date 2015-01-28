#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#include "bubblesort.h"
#include "quicksort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "shellsort.h"

typedef struct algorithm {
	char name[30];
	void (*function)(array_t*, int (*)(array_t*,int));
} algorithm_t;

extern const algorithm_t AVAILABLE_ALGOS[];

#endif
