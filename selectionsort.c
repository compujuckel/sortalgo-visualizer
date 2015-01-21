#include "selectionsort.h"
#include "array.h"

void selectionsort(array_t* arr, void (*update)(array_t*,int))
{
  int i,j, temp;
  for(i=0;i<arr->length;i++){
      for(j=i+1;j<arr->length;j++){
           if(arr->ptr[i]>arr->ptr[j]){
               temp=arr->ptr[i];
              arr->ptr[i]=arr->ptr[j];
              arr->ptr[j]=temp;
              update(arr, j);
           }
      }
  }
}
