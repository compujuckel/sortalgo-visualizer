#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "algorithm.h"
#include "graphics.h"
#include "array.h"
#include "util.h"
#include "timer.h"

//defs
#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define ARRAY_LENGTH 100
#define DELAY 10         //Delay between Array accesses in ms

int main(){

	srand(time(NULL));                    //init randomizer

	g_init(WINDOW_SIZE_X, WINDOW_SIZE_Y, DELAY);
	a_init(ARRAY_LENGTH);

	int i;
	for(i = 0; AVAILABLE_ALGOS[i].function != NULL; i++) {
		printf("Using %s algorithm\n",AVAILABLE_ALGOS[i].name);

		array_t* copy = a_get_copy();
		
		timer_start();
		AVAILABLE_ALGOS[i].function(copy, &g_update);

		printf("Time: %f seconds\n",timer_status());
		free(copy->ptr);
		free(copy);
	}

	SDL_Event ev;
	while(SDL_WaitEvent(&ev)) {
		if(ev.type == SDL_QUIT)
			break;
	}

	//Quit
	g_cleanup();
	a_cleanup();
	return EXIT_SUCCESS;
}
