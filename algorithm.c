#include "algorithm.h"
#include "array.h"
#include "bubblesort.h"
#include "quicksort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "shellsort.h"

const algorithm_t AVAILABLE_ALGOS[] = {
	{ "Bubble Sort", &bubblesort },
	{ "Quick Sort", &quicksort },
	{ "Insertion Sort", &insertion },
  { "Selection Sort", &selectionsort },
  { "Shell Sort", &ShellSort },
	{ "", NULL }
};
