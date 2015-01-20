#include "graphics.h"
#include "util.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//Pointer for SDL
static SDL_Window* window = NULL;
static SDL_Renderer* render = NULL;
static TTF_Font* font = NULL;

static int delay;

//Intitializes all necessary SDL objects
void g_init(int wsize_x, int wsize_y, int d) {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Test", 100, 100, wsize_x, wsize_y, 0); //creates a Window
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);            //creates Renderer
	delay = d;

	TTF_Init();
	font = TTF_OpenFont("OpenSans-Regular.ttf", 14);
	if(font == NULL)
		exit_with_error("could not open font");
}

void g_cleanup(void) {
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

static void g_renderTexture(SDL_Texture* tex, int x, int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

	SDL_RenderCopy(render, tex, NULL, &dst);
}

static void g_print(int x, int y, char* text)  {
	SDL_Color white = {255, 255, 255};
	SDL_Surface* f = TTF_RenderText_Blended(font, text, white);
	SDL_Texture* t = SDL_CreateTextureFromSurface(render, f);

	SDL_FreeSurface(f);
	g_renderTexture(t, x, y);
	SDL_DestroyTexture(t);
}

static void g_printf(int x, int y, const char* format, ...) {
	char buffer[200];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 200, format, args);
	g_print(x, y, buffer);
	va_end(args);
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

	//g_printf(10, 10, "Hello %d",10);
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
