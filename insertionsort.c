#include "insertionsort.h"
#include "array.h"

void insertion(array_t* arr, int (*update)(array_t*,int))
{
 int i,j,tmp;
 for(i=0; i<arr->length; i++)
 {
   for(j=i-1; j>=0; j--)
   {
    if(arr->ptr[j]>arr->ptr[j+1])
    {
      tmp=arr->ptr[j];
      arr->ptr[j]=arr->ptr[j+1];
      arr->ptr[j+1]=tmp;
      if(update(arr, j)) return;
    }
    else
      break;
   }
 }
}
