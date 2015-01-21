#include "array.h"

//partition function for quicksort
static int partition(array_t* a,  int l, int r, void (*update)(array_t*,int)) {
	int pivot, i, j, t;
	pivot = a->ptr[l];
	i = l; j = r+1;

	while(1)
	{
		do{
			++i;

			update(a, i);                       //calls the print array function

		} while( i <= r && a->ptr[i] <= pivot);
		do{
			--j;

			update(a, j);                       //calls the print array function

		}while( a->ptr[j] > pivot );

		if( i >= j ) break;

		t = a->ptr[i]; a->ptr[i] = a->ptr[j]; a->ptr[j] = t;

	}
	t = a->ptr[l]; a->ptr[l] = a->ptr[j]; a->ptr[j] = t;

	update(a, j);                           //calls the print array function

	return j;
}

//actual quicksort function
static void quicksort_internal(array_t* a, int l, int r, void (*update)(array_t*,int))
{
	int j;
	if( l < r )
	{
		// divide and conquer
		j = partition( a, l, r, update);
		quicksort_internal( a, l, j-1, update);
		quicksort_internal( a, j+1, r, update);
	}

}

void quicksort(array_t* a, void (*update)(array_t*,int)) {
	quicksort_internal(a, 0, a->length-1, update);
}
