#include "search.h"


//Search algorithms
int binary_search(int *array, size_t size, int searchValue) {

    int low = 0;
    int high = size - 1;
    int middle = 0;

    while(high >= low) {
        middle = (high + low)/2;

        if(array[middle] > searchValue) {
            high = middle - 1; //High slowly creeps down
        } else if(array[middle] < searchValue) {
            low = middle + 1; //Low slowly creeps up
        } else {
            return middle; //Return index found
        }
    }
    
    return -1; //Not found
}


int recursive_binary_search(int *array, int searchValue, int low, int high) {

    int middle = (high + low)/2;
    if(high < low) {

        //Last possible check - so check if element is in the array
        //If not then just return -1
        if(array[middle] == searchValue) {
            return middle; //Element in array
        } else {
            return -1; //Element not in array
        }   

    } else {


        if(array[middle] > searchValue) {
            high = middle -1;
            middle = recursive_binary_search(array, searchValue, low, high);
        } else if(array[middle] < searchValue) {
            low = middle + 1; //Low slowly creeps up
            middle = recursive_binary_search(array, searchValue, low, high);
        } else {
            return middle; //Return index found
        }

    }
    return middle;
}

