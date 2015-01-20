#include "graphics.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//Pointer for SDL
static SDL_Window* window;
static SDL_Renderer* render;

static int delay;

//Intitializes all necessary SDL objects
void g_init(int wsize_x, int wsize_y, int d) {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Test", 100, 100, wsize_x, wsize_y, 0); //creates a Window
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);            //creates Renderer
	delay = d;
}

void g_cleanup(void) {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//This function displays and int array as a number of boxes with the length of its corresponding array-element
void g_update(int *array, int selection, int length) {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			g_cleanup();
			exit(EXIT_SUCCESS);
		}
	}

	SDL_RenderClear(render);                      //cear screen

	int wsize_x, wsize_y;
	SDL_GetWindowSize(window, &wsize_x, &wsize_y);
	float elem_height = wsize_y / length;

	float xPos = 0;                             //starting x-position for first box
	float yPos = wsize_y;             //starting y position

	float width = wsize_x / length;  //compute width of the boxes

	SDL_Rect r;
	r.w = width - 1;                           //apply width to sdl-rectangle

	int i;
	for(i = 0; i < length; i++){
		xPos = i * width;                                                      //x position
		r.x = xPos;                                                       //apply x-pos
		r.h = elem_height * array[i];                                              //apply height
		r.y = yPos - elem_height * array[i];                                       //this is necessary because sdl computes the y positon of a rect from the top of it

		if(i == selection) {
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		} else {
			SDL_SetRenderDrawColor(render, 127, 127, 127, 255);
		}
		SDL_RenderFillRect(render, &r);

		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	}

	SDL_RenderPresent(render);                                             //Actual rendering
	SDL_Delay(delay);
}
