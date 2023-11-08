#include <stdio.h> 
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;

void selectionSort(int arr[], int size)
{ 
  int min;
  int hold;

  for(int i = 0; i < size-1; i++){
    min = i;
    number_swaps++;
    for(int j = i + 1; j < size; j++){
        number_comparisons++;
        if(arr[j] < arr[min]){
            min = j;

        }
    }

    if(min != i){
        hold = arr[min];
        arr[min] = arr[i];
        arr[i] = hold;
    }

  }
} 

void insertionSort(int arr[], int size) 
{ 
  int key;
  int j;

  for(int i = 1; i < size; i++){
    key = arr[i];
    j = i - 1;
    number_comparisons++;

    while(j >= 0 && arr[j] > key){
        arr[j+1] = arr[j];
        j = j - 1;
        number_swaps++;
        number_comparisons++;
    }
    arr[j + 1] = key;

  }

}




void quickSort(int arr[], int size)
{ 

    int high = size-1;
    int low = 0;
    newQuickSort(arr, high, low);


}

void newQuickSort(int arr[], int high, int low){
    
    int pivotIndex;

    if(low<high){
        number_comparisons++;
        pivotIndex = partition(arr, high, low);
        newQuickSort(arr, pivotIndex - 1, low);
        newQuickSort(arr, high, pivotIndex + 1);

    }
}

int partition(int arr[], int high, int low){
    
    int pivot = arr[high];
    int i = low - 1;
    int temp;
    number_comparisons++;

    for(int j = low; j < high; j++){
        number_comparisons++;
        if(arr[j] <= pivot){
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            number_swaps++;
        }
    }

    temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    number_swaps++;

    return (i + 1);

}