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

int main(){
	SDL_Event e;
	int quit = 0;
	int i;
	int algo;
	int pos[10][2];  //gets x and y positions of buttons for algorithms
	int size[10][2]; //gets x and y size of buttons for algorithms

	srand(time(NULL));                    //init randomizer

	g_init(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	a_init(g_getArrayLength());

	//main loop
	while(!quit){
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = 1;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					//check delay buttons
					for(i = 0; i < 7; i++){
						if(e.button.x > 10 && e.button.x < 120 &&
								e.button.y > 80 + 60*i && e.button.y < 135 + 60*i)
						{
							printf("Delay set to %d ms \n", i*5);
							g_updateDelay(i*5);
						}
					}
					//check array length buttons
					for(i = 0; i < 4; i++){
						int wsize_x = g_getWindowX();
						if(e.button.x > wsize_x -80 && e.button.x < wsize_x -10 &&
								e.button.y > 80 + 60*i && e.button.y < 135 + 60*i)
						{
							g_setArrayLength((i+1)*50);
							a_init(g_getArrayLength());
							printf("Array length set to %d \n", g_getArrayLength());
						}
					}
					//check algo buttons
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
