#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "algorithm.h"
#include "graphics.h"
#include "util.h"

//defs
#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define ARRAY_LENGTH 100
#define DELAY 10         //Delay between Array accesses in ms

int array_master[ARRAY_LENGTH]; //Array that will be sorted and displayed


//Randomizes Array entries
void shuffle(int *array, size_t n){
	if (n > 1){

		size_t i;
		for (i = 0; i < n - 1; i++){

			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;

		}
	}
}

//intialize Array with number from 0 to ARRAY_LENGTH and randomize it
void initArray(){
	int i;
	for(i=0; i<=ARRAY_LENGTH; i++){
		array_master[i] = i;
	}
	shuffle(array_master, ARRAY_LENGTH);
}


//-----------------------------------------------------------
//--------Test Code for sorting algorithms-------------------


int main(){

	srand(time(NULL));                    //init randomizer

	g_init(WINDOW_SIZE_X, WINDOW_SIZE_Y, DELAY);
	initArray();

	int i;
	for(i = 0; AVAILABLE_ALGOS[i].function != NULL; i++) {
		printf("Using %s algorithm\n",AVAILABLE_ALGOS[i].name);
		// Create a copy of the master array the algorithm can work on
		int* array_copy = malloc(sizeof(int)*ARRAY_LENGTH);
		if(array_copy == NULL)
			exit_with_error("malloc failed");
		memcpy(array_copy, array_master, sizeof(int)*ARRAY_LENGTH);

		AVAILABLE_ALGOS[i].function(array_copy, ARRAY_LENGTH, &g_update);

		free(array_copy);
	}

	SDL_Event ev;
	while(SDL_WaitEvent(&ev)) {
		if(ev.type == SDL_QUIT)
			break;
	}

	//Quit
	g_cleanup();
	return 0;
}
