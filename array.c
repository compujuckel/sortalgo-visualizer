#include "array.h"
#include "util.h"

#include <stdlib.h>
#include <string.h>

static int* array_master = NULL;
static int length;

//Randomizes Array entries
static void shuffle(int* array, int l){
	if (l > 1){
		int i;
		for (i = 0; i < l - 1; i++){
			size_t j = i + rand() / (RAND_MAX / (l - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}

//intialize Array with number from 0 to ARRAY_LENGTH and randomize it
void a_init(int l) {
	if(array_master != NULL)
		free(array_master);

	array_master = malloc(sizeof(int)*l);
	if(array_master == NULL)
		exit_with_error("malloc failed");

	length = l;

	int i;
	for(i = 0; i < length; i++){
		array_master[i] = i;
	}
	shuffle(array_master, length);
}

int* a_get_copy(void) {
	int* copy = malloc(sizeof(int)*length);
	if(copy == NULL)
		exit_with_error("malloc failed");

	memcpy(copy,array_master,sizeof(int)*length);
	return copy;
}

void a_cleanup(void) {
	free(array_master);
}
