#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "algorithm.h"

//defs
#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define ARRAY_LENGTH 100
#define DELAY 10         //Delay between Array accesses in ms
float elem_height = WINDOW_SIZE_Y / ARRAY_LENGTH;

//Pointer for SDL
SDL_Window* window;
SDL_Renderer* render;

int sortMe[ARRAY_LENGTH]; //Array that will be sorted and displayed

//intialize Array with number from 0 to ARRAY_LENGTH
void initArray(){
	int i;
	for(i=0; i<=ARRAY_LENGTH; i++){
		sortMe[i] = i;
	}
}

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

//Intitializes all necessary SDL objects
void initSDL(){

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Test", 100, 100, WINDOW_SIZE_X, WINDOW_SIZE_Y, 0); //creates a Window
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);            //creates Renderer
	SDL_Surface* screen = SDL_GetWindowSurface(window);

}

void cleanup() {
	SDL_DestroyRenderer(render);
	//SDL_DestroyWindow(window); // TODO: fix segfault
	SDL_Quit();
}

//This function displays and int array as a number of boxes with the length of its corresponding array-element
void printArray(int *sortMe, int selection){
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			cleanup();
			exit(0);
		}
	}

	SDL_RenderClear(render);                      //cear screen

	float xPos = 0;                             //starting x-position for first box
	float yPos = WINDOW_SIZE_Y;             //starting y position
	int i;

	float width = WINDOW_SIZE_X / ARRAY_LENGTH;  //compute width of the boxes

	SDL_Rect r;
	r.w = width - 1;                           //apply width to sdl-rectangle

	for(i=0; i<=ARRAY_LENGTH; i++){
		xPos = i*width;                                                      //x position
		r.x = xPos;                                                       //apply x-pos
		r.h = elem_height * sortMe[i];                                              //apply height
		r.y = yPos - elem_height * sortMe[i];                                       //this is necessary because sdl computes the y positon of a rect from the top of it

		if(i == selection) {
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		} else {
			SDL_SetRenderDrawColor(render, 127, 127, 127, 255);
		}
		SDL_RenderFillRect(render, &r);

		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	}

	SDL_RenderPresent(render);                                             //Actual rendering
	SDL_Delay(DELAY);
}

//-----------------------------------------------------------
//--------Test Code for sorting algorithms-------------------


int main(){

	srand(time(NULL));                    //init randomizer

	initSDL();
	initArray();

	int i;
	for(i = 0; AVAILABLE_ALGOS[i].function != NULL; i++) {
		printf("Using %s algorithm\n",AVAILABLE_ALGOS[i].name);
		shuffle(sortMe,ARRAY_LENGTH);
		AVAILABLE_ALGOS[i].function(sortMe, ARRAY_LENGTH, &printArray);
	}

	printArray(sortMe, 0);

	SDL_Event ev;
	while(SDL_WaitEvent(&ev)) {
		if(ev.type == SDL_QUIT)
			break;
	}

	//Quit
	cleanup();
	return 0;
}
