#include "array.h"
#include "util.h"

#include <stdlib.h>
#include <string.h>

static array_t* array_master = NULL;

//Randomizes Array entries
static void shuffle(array_t* array){
	if (array->length > 1){
		int i;
		for (i = 0; i < array->length - 1; i++){
			size_t j = i + rand() / (RAND_MAX / (array->length - i) + 1);
			int t = array->ptr[j];
			array->ptr[j] = array->ptr[i];
			array->ptr[i] = t;
		}
	}
}

//intialize Array with number from 0 to ARRAY_LENGTH and randomize it
void a_init(int l) {
	if(array_master != NULL)
		free(array_master);

	array_master = malloc(sizeof(array_t));
	if(array_master == NULL)
		exit_with_error("malloc failed");

	array_master->ptr = malloc(l * sizeof(int));
	if(array_master->ptr == NULL)
		exit_with_error("malloc failed");

	array_master->length = l;
	array_master->acount = 0;

	int i;
	for(i = 0; i < array_master->length; i++){
		array_master->ptr[i] = i;
	}
	shuffle(array_master);
}

array_t* a_get_copy(void) {
	array_t* copy = malloc(sizeof(array_t));
	if(copy == NULL)
		exit_with_error("malloc failed");
	copy->length = array_master->length;
	copy->acount = 0;
	copy->ptr = malloc(sizeof(int) * copy->length);
	if(copy->ptr == NULL)
		exit_with_error("malloc failed");

	memcpy(copy->ptr,array_master->ptr,sizeof(int) * copy->length);
	return copy;
}

void a_cleanup(void) {
	free(array_master->ptr);
	free(array_master);
}
