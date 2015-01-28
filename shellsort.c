#include "bubblesort.h"
#include "array.h"
#include "graphics.h"

void ShellSort(array_t* array, int (*update)(array_t*,int))
{
  int i, j, increment, temp;
  for(increment = array->length/2;increment > 0; increment /= 2)
    {
      for(i = increment; i<array->length; i++)
        {
          temp = array->ptr[i];
          if(update(array, j)) return;
          for(j = i; j >= increment ;j-=increment)
            {
              if(temp < array->ptr[j-increment])
                {
                  array->ptr[j] = array->ptr[j-increment];
                  if(update(array, j)) return;
                }
                else
                  {
                    break;
                  }
             }
              array->ptr[j] = temp;
              if(update(array, j)) return;
          }
      }
}
