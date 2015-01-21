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
#define DELAY 5         //Delay between Array accesses in ms

int main(){
	SDL_Event e;
	int quit = 0;
	int i;
	int algo;
	int pos[10][2];  //gets x and y positions of buttons for algorithms
	int size[10][2]; //gets x and y size of buttons for algorithms

	srand(time(NULL));                    //init randomizer

	g_init(WINDOW_SIZE_X, WINDOW_SIZE_Y, DELAY);
	a_init(ARRAY_LENGTH);

	//main loop
	while(!quit){
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				g_cleanup();
				quit = 1;
		  }
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					for(i = 0; AVAILABLE_ALGOS[i].function != NULL; i++)
						{
							if(e.button.x > pos[i][0] && e.button.x < pos[i][0] + size[i][0] &&
								 e.button.y > pos[i][1] && e.button.y < pos[i][1] + size[i][1])
							{
							algo = i;

							printf("Using %s algorithm\n",AVAILABLE_ALGOS[algo].name);

							array_t* copy = a_get_copy();

							timer_start();
							AVAILABLE_ALGOS[algo].function(copy, &g_update);

							printf("Time: %f seconds\n",timer_status());
							free(copy->ptr);
							free(copy);
							break;
						  }
						}

					}
				}
				else g_menu(&pos, &size);
				}
			}

	//Quit
	g_cleanup();
	a_cleanup();
	return EXIT_SUCCESS;
}
