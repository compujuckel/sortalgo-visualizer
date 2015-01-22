#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"
#include "timer.h"
#include "util.h"
#include "array.h"
#include "algorithm.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//Pointer for SDL
static SDL_Window* window = NULL;
static SDL_Renderer* render = NULL;
static TTF_Font* font14, *font40 = NULL;

static int delay = 10;                     //delay between updates in ms
static int array_length = 100;

//Intitializes all necessary SDL objects
void g_init(int wsize_x, int wsize_y) {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Sortme", 100, 100, wsize_x, wsize_y, 0);             //creates a Window
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);            //creates Renderer

	TTF_Init();
	font14 = TTF_OpenFont("OpenSans-Regular.ttf", 14);
	if(font14 == NULL)
		exit_with_error("could not open font");
	font40 = TTF_OpenFont("OpenSans-Regular.ttf", 40);
	if(font40 == NULL)
		exit_with_error("could not open font");
}

void g_cleanup(void) {
	TTF_CloseFont(font14);
	TTF_CloseFont(font40);
	TTF_Quit();
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void g_updateDelay(int d){
	delay = d;
}

int g_getArrayLength(){
	return array_length;
}

void g_setArrayLength(int l){
	array_length =l;
}


static void g_getTexSize(char* text, TTF_Font *font, int size[2]) {
	SDL_Color white = {255, 255, 255};
	SDL_Surface* f = TTF_RenderText_Blended(font, text, white);
	SDL_Texture* t = SDL_CreateTextureFromSurface(render, f);
	SDL_QueryTexture(t, NULL, NULL, &size[0], &size[1]);
}

static void g_renderTexture(SDL_Texture* tex, int x, int y, int fill) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	if(fill){
		SDL_SetRenderDrawColor(render, 127, 127, 127, 255);
		SDL_RenderFillRect(render, &dst);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	}
	if(fill == 2){
		SDL_SetRenderDrawColor(render, 127, 0, 0, 255);
		SDL_RenderFillRect(render, &dst);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	}
	SDL_RenderCopy(render, tex, NULL, &dst);
}

static void g_print(int x, int y, char* text, TTF_Font *font, int fill)  {
	SDL_Color white = {255, 255, 255};
	SDL_Surface* f = TTF_RenderText_Blended(font, text, white);
	SDL_Texture* t = SDL_CreateTextureFromSurface(render, f);

	SDL_FreeSurface(f);
  g_renderTexture(t, x, y, fill);
	SDL_DestroyTexture(t);
}

static void g_printf(int x, int y, TTF_Font *font, int fill, const char* format, ...) {
	char buffer[200];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 200, format, args);
	g_print(x, y, buffer, font, fill);
	va_end(args);
}

void g_menu(int pos[10][2], int size[10][2]){
	SDL_RenderClear(render);

	int wsize_x, wsize_y;
	SDL_GetWindowSize(window, &wsize_x, &wsize_y);

	int tmpSize[2];
	int i;
	//Algo buttons
	for(i = 0; AVAILABLE_ALGOS[i].function != NULL; i++) {
		if(i == 0) g_print(wsize_x/2 - 100, 10, "Algorithms:", font40, 0);
		g_getTexSize(AVAILABLE_ALGOS[i].name, font40, tmpSize);
		size[i][0] = tmpSize[0];
		size[i][1] = tmpSize[1];
		pos[i][0] = wsize_x /2 - size[i][0] / 2;
		pos[i][1] = wsize_y/10  + size[i][1] / 2 + i*(size[i][1]+5);
		g_print(pos[i][0], pos[i][1], AVAILABLE_ALGOS[i].name, font40, 1);
	}
	//Delay buttons
	g_print(10, 10, "Delay:", font40, 0);
	for(i = 0; i < 7; i++){
		if(i*5 == delay) g_printf(10, 80 + i*60, font40, 2, "%d ms", i*5);
		else g_printf(10, 80 + i*60, font40, 1, "%d ms", i*5);
	}
	//Array size buttons
	g_print(wsize_x - 200, 10, "Array size:", font40, 0);
	for(i = 0; i < 4; i++){
		if((i+1)*50 == array_length) g_printf(wsize_x - 80, 80 + i*60, font40, 2, "%d", (i+1)*50);
		else g_printf(wsize_x - 80, 80 + i*60, font40, 1, "%d", (i+1)*50);
	}

	SDL_RenderPresent(render);
}

//This function displays and int array as a number of boxes with the length of its corresponding array-element
int g_update(array_t* a, int selection) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if(e.type == SDL_QUIT) {
			g_cleanup();
			exit(EXIT_SUCCESS);
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
			return 1;
		}
	}

	SDL_RenderClear(render);                      //cear screen

	int wsize_x, wsize_y;
	SDL_GetWindowSize(window, &wsize_x, &wsize_y);
	float elem_height = wsize_y / a->length;

	float xPos = 0;                             //starting x-position for first box
	float yPos = wsize_y;             //starting y position

	float width = wsize_x / a->length;  //compute width of the boxes

	SDL_Rect r;
	r.w = width - 1;                           //apply width to sdl-rectangle

	int i;
	for(i = 0; i < a->length; i++){
		xPos = i * width;                                                      //x position
		r.x = xPos;                                                       //apply x-pos
		r.h = elem_height * a->ptr[i];                                              //apply height
		r.y = yPos - elem_height * a->ptr[i];                                       //this is necessary because sdl computes the y positon of a rect from the top of it

		if(i == selection) {
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		} else {
			SDL_SetRenderDrawColor(render, 127, 127, 127, 255);
		}
		SDL_RenderFillRect(render, &r);

		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	}
	g_printf(10, 10, font14, 0, "Elapsed time: %f",timer_status());
	g_printf(10, 30, font14, 0, "Updates: %d",++a->acount);

	SDL_RenderPresent(render);                                             //Actual rendering
	SDL_Delay(delay);
	return 0;
}
