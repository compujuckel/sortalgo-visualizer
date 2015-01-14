


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//defs
#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define ARRAY_LENGTH 100
#define DELAY 10         //Delay between Array accesses in ms

//Pointer for SDL
SDL_Window* window;
SDL_Texture *normal, *selected;
SDL_Renderer* render;
SDL_Rect test;

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

  normal = IMG_LoadTexture(render, "grey.bmp");                                 //load picture for the normal colored boxes
  selected = IMG_LoadTexture(render, "red.bmp");                                //load picture for the red boxes (selected ones)

  SDL_Surface* screen = SDL_GetWindowSurface(window);

}

//This function displays and int array as a number of boxes with the length of its corresponding array-element
void printArray(int *sortMe, int selection){

  SDL_RenderClear(render);                      //cear screen

  float xPos = 10;                             //starting x-position for first box
  float yPos = WINDOW_SIZE_Y - 10;             //starting y position
  int i;

  float width = WINDOW_SIZE_X / ARRAY_LENGTH;  //compute width of the boxes
  test.w = width - 1;                           //apply width to sdl-rectangle

  //this iterates through the array and applys an x-coordinate and a height(equal to the array value * 4) to each rectangle and copies it on the screen
  for(i=0; i<=ARRAY_LENGTH; i++){
    xPos = i*width;                                                      //x position
    test.x = xPos;                                                       //apply x-pos
    test.h = sortMe[i] * 4;                                              //apply height
    test.y = yPos - sortMe[i] * 4;                                       //this is necessary because sdl computes the y positon of a rect from the top of it

    if(i == selection) SDL_RenderCopy(render, selected, NULL, &test);    //print red box if element is selected
    else SDL_RenderCopy(render, normal, NULL, &test);                    //else print normal box
  }

  SDL_RenderPresent(render);                                             //Actual rendering
}

//-----------------------------------------------------------
//--------Test Code for sorting algorithms-------------------


void bubbleSort(){
    int x;
    int y;
    for(x=0; x<ARRAY_LENGTH; x++)
        {
            for(y=0; y<ARRAY_LENGTH-1; y++)
            {
                if(sortMe[y]>sortMe[y+1])
                {
                    int temp = sortMe[y+1];
                    sortMe[y+1] = sortMe[y];
                    sortMe[y] = temp;

                    printArray(sortMe, y+1);   //calls the print array function after every iteration of the algorithm
                    SDL_Delay(DELAY);          //wait DELAY ms
                }
            }
        }
}

//partition function for quicksort
int partition( int a[], int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;

   while( 1)
   {
   	do{
   	    ++i;

   	    printArray(a, i);                       //calls the print array function
        SDL_Delay(DELAY);

   	} while( a[i] <= pivot && i <= r );
   	do{
   	    --j;

   	    printArray(a, j);                       //calls the print array function
        SDL_Delay(DELAY);

    }while( a[j] > pivot );

   	if( i >= j ) break;

   	t = a[i]; a[i] = a[j]; a[j] = t;

   }
   t = a[l]; a[l] = a[j]; a[j] = t;

   printArray(a, j);                           //calls the print array function
   SDL_Delay(DELAY);

   return j;
}

//actual quicksort function
void quickSort( int a[], int l, int r)
{
   int j;
   if( l < r )
   {
   	// divide and conquer
       j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }

}


int main(){

  srand(time(NULL));                    //init randomizer

  initSDL();
  initArray();

  shuffle(sortMe,ARRAY_LENGTH);         //shuffle the array

  bubbleSort();                         //show bubblesort

  shuffle(sortMe,ARRAY_LENGTH);         //shuffle again

  quickSort(sortMe, 0, ARRAY_LENGTH);   //show quicksort

  printArray(sortMe,0);

  SDL_Delay(10000);                    //wait

  //Quit
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}