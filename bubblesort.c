#include "bubblesort.h"

void bubblesort(int* array, int length, void (*update)(int*,int,int)) {
    int x;
    int y;
    for(x=0; x < length; x++)
    {
        for(y=0; y < length-1; y++)
        {
            if(array[y] > array[y+1])
            {
                int temp = array[y+1];
                array[y+1] = array[y];
                array[y] = temp;
                update(array, y+1, length);   //calls the print array function after every iteration of the algorithm
             }
         }
    }
}
