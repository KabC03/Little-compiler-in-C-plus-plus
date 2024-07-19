#include "sort.h"


/*
 All functions take int array (arr) and size of array (numel)
 
 Return bool depending on if sort was successful
 */

//Sort algorithms

void printArr(int * arr, int numel) {
    int index = numel - 1;
    printf("[");
    for (int i = 0; i < index; i++)
    {
        printf("%d, ",arr[i]);
    }
    printf("%d",arr[index]);
    printf("]\n");
    
}


bool bubble(int *arr, int numel) {
    if(arr == NULL || numel < 1) return false;
    
    int index = numel - 1;
    int swapVal = 0;
    bool swapped = false;
    
    while(1)  {

        swapped = false;
        for (int i = 0; i < index; i++) {
            if (arr[i] > arr[i+1]) {
                
                swapVal = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = swapVal;
                swapped = true;
            }
        }

        if(swapped == false) {
            break; // Zero swaps indicate array is sorted
        }

        index--; //Decrement - because largest element is GUARANTEED to be at the end
    }


    return true;
}



bool recursive_bubble(int *array, size_t size) {

    if(array == NULL || size == 0) {
        return false;
    } else if(size == 1) {
        return true;
    } else {
        int temp = 0;
        for (int i = 0; i < size - 1; i++) {
            if (array[i] > array[i+1]) {
                
                temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
            }
        }
        size--; //Last position GUARANTEED to have largest value, so only need to sort 0->last-1 every iteration
    }


    return true;
}




bool selection(int * arr, int numel) {
    if(arr == NULL) return false;
    
    int index = numel - 1;
    int currentMinIndex;
    int intermediate;
    
    for (int i = 0; i < index; i++) {

        currentMinIndex = i;
        for (int j = i + 1; j < index + 1; j++) {
            
            if (arr[currentMinIndex] > arr[j]) {
                currentMinIndex = j;
            }
        }
        
        intermediate = arr[i];
        arr[i] = arr[currentMinIndex];
        arr[currentMinIndex] = intermediate;
        
    }
    return true;
}


bool bogo(int * arr, int numel) {
    srand((int)time(NULL));
    
    if(arr == 0) return false;
    if (numel == 1) return true;
    int index = numel - 1;
    bool sorted = false;
    
    int intermediate;

    while(sorted == false)
    {

        for (int i = 0; i < (index/2) + 1; i++) {
            
            int randIndex = rand()%numel;
            
            intermediate = arr[i];
            
            arr[i] = arr[randIndex];
            arr[randIndex] = intermediate;
        }
        
        for (int i = 0; i < index; i++) {
            sorted = true;
            if(arr[i] > arr[i+1])
            {
                sorted = false;
                break;
            }
        }
        
        
    }
    
    
    
    
    return true;
}

bool insertion(int * arr, int numel) {
    if(arr == NULL) return false;
    
    int index = numel - 1;
    int intermediate;
    
    for (int i = 0; i < index; i++)
    {
        int j = i;
        
        while(arr[i] > arr[j + 1] && j < index)
        {
            j++;
        }
        intermediate = arr[i];
        arr[i] = arr[j];
        arr[j] = intermediate;
    }

    return true;
}




