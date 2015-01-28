#include "array.h"

//partition function for quicksort
static int partition(array_t* a,  int l, int r, int (*update)(array_t*,int)) {
	if ( update(a, 0) ) return -1;
	int pivot, i, j, t;
	pivot = a->ptr[l];
	i = l; j = r+1;

	while(1)
	{
		do{
			if(update(a, i)) return -1;                       //calls the print array function

			++i;
		} while( i <= r && a->ptr[i] <= pivot);
		do{
			if(update(a, j)) return -1;                       //calls the print array function

			--j;
		}while( a->ptr[j] > pivot );

		if( i >= j ) break;

		t = a->ptr[i]; a->ptr[i] = a->ptr[j]; a->ptr[j] = t;

	}
	t = a->ptr[l]; a->ptr[l] = a->ptr[j]; a->ptr[j] = t;

	if(update(a, i)) return -1;                           //calls the print array function

	return j;
}

//actual quicksort function
static void quicksort_internal(array_t* a, int l, int r, int (*update)(array_t*,int))
{
	int j;
	if( l < r )
	{
		// divide and conquer
		j = partition( a, l, r, update);
		if(j == -1) return;
		quicksort_internal( a, l, j-1, update);
		quicksort_internal( a, j+1, r, update);
	}
}

void quicksort(array_t* a, int (*update)(array_t*,int)) {
	quicksort_internal(a, 0, a->length-1, update);
}
