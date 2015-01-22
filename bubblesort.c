#include "bubblesort.h"
#include "array.h"
#include "graphics.h"

#include <SDL2/SDL.h>

SDL_Event e;

void bubblesort(array_t* a, int (*update)(array_t*,int)) {
    int x;
    int y;
    for(x=0; x < a->length; x++)
    {
        for(y=0; y < a->length-1; y++)
        {
            if(a->ptr[y] > a->ptr[y+1])
            {
                int temp = a->ptr[y+1];
                a->ptr[y+1] = a->ptr[y];
                a->ptr[y] = temp;
                if( update(a, y+1) ) return;   //calls the print array function after every iteration of the algorithm
             }
         }
    }
}
