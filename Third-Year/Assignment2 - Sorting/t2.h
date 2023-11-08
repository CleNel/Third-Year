#ifndef T2_H_
#define T2_H_
void selectionSort(int arr[], int size);
void insertionSort(int arr[], int size);
void quickSort(int arr[], int size);
int partition(int array[], int start, int end);
void newQuickSort(int arr[], int high, int low);

extern int number_comparisons;
extern int number_swaps;


#endif