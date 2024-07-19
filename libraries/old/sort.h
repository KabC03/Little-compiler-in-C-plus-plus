#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#define len(arr) sizeof(arr)/sizeof(arr[0])


/*

    Parameters:
        arr - Pointer to the array of integers to be sorted.
        numel - Number of elements in the array.

    Returns: 
        bool - true if the sorting was successful, false otherwise.
        void - none
*/


void printArr(int * arr, int numel);
bool bubble(int * arr, int numel);
bool insertion(int * arr, int numel);
bool selection(int * arr, int numel);
bool bogo(int * arr, int numel);
