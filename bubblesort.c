#include "bubblesort.h"
#include "array.h"

void bubblesort(array_t* a, void (*update)(array_t*,int)) {
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
                update(a, y+1);   //calls the print array function after every iteration of the algorithm
             }
         }
    }
}
