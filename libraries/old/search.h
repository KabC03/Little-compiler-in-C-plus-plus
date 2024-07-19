#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#define len(arr) sizeof(arr)/sizeof(arr[0])


int binary_search(int *array, size_t size, int searchValue); //Returns index of element, -1 if failure
int recursive_binary_search(int *array, int searchValue, int low, int high);



