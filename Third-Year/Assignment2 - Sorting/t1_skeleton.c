#include <stdio.h>
#include <stdlib.h>
#include "t1.h"


//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    for(int i = 0; i < size; i++){
        array[i] = i;
    }    
}
//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
    for(int i = 0; i < size; i++){
        array[i] = size-1-i;
    }
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size)
{
    int num = (rand() % size);

    for(int i = 0; i < size; i++){
        array[i] = num;
    }
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size)
{
    for(int i = 0; i < size; i++){
        array[i] = (rand() % size);
    }
    
}


//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
    int used[size];
    int index = (rand() % size);

    for(int i = 0; i < size; i++){
        used[i] = -1;
    }

    for(int j = 0; j < size; j++){
        while(used[index] != -1){
            index = (rand() % size);
        }
        array[j] = index;
        used[index] = index;
    }
    
}

void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}