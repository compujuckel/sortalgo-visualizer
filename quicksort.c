
//partition function for quicksort
static int partition( int a[], int l, int r, void (*update)(int*,int)) {
	int pivot, i, j, t;
	pivot = a[l];
	i = l; j = r+1;

	while( 1)
	{
		do{
			++i;

			update(a, i);                       //calls the print array function

		} while( a[i] <= pivot && i <= r );
		do{
			--j;

			update(a, j);                       //calls the print array function

		}while( a[j] > pivot );

		if( i >= j ) break;

		t = a[i]; a[i] = a[j]; a[j] = t;

	}
	t = a[l]; a[l] = a[j]; a[j] = t;

	update(a, j);                           //calls the print array function

	return j;
}

//actual quicksort function
static void quicksort_internal( int a[], int l, int r, void (*update)(int*,int))
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

void quicksort(int* array, int length, void (*update)(int*,int)) {  
	quicksort_internal(array, 0, length, update);	
}
