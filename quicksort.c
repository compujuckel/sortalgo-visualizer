
//partition function for quicksort
static int partition( int a[], int l, int r, int length, void (*update)(int*,int,int)) {
	int pivot, i, j, t;
	pivot = a[l];
	i = l; j = r+1;

	while(1)
	{
		do{
			++i;

			update(a, i, length);                       //calls the print array function

		} while( i <= r && a[i] <= pivot);
		do{
			--j;

			update(a, j, length);                       //calls the print array function

		}while( a[j] > pivot );

		if( i >= j ) break;

		t = a[i]; a[i] = a[j]; a[j] = t;

	}
	t = a[l]; a[l] = a[j]; a[j] = t;

	update(a, j, length);                           //calls the print array function

	return j;
}

//actual quicksort function
static void quicksort_internal( int a[], int l, int r, int length, void (*update)(int*,int,int))
{
	int j;
	if( l < r )
	{
		// divide and conquer
		j = partition( a, l, r, length, update);
		quicksort_internal( a, l, j-1, length, update);
		quicksort_internal( a, j+1, r, length, update);
	}

}

void quicksort(int* array, int length, void (*update)(int*,int,int)) {
	quicksort_internal(array, 0, length-1, length, update);
}
