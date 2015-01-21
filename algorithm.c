#include "algorithm.h"
#include "array.h"
#include "bubblesort.h"
#include "quicksort.h"
#include "insertionsort.h"
#include "selectionsort.h"

const algorithm_t AVAILABLE_ALGOS[] = {
	{ "Bubble Sort", &bubblesort },
	{ "Quicksort", &quicksort },
	{ "Insertionsort", &insertion },
  { "Selectionsort", &selectionsort },
	{ "", NULL }
};
