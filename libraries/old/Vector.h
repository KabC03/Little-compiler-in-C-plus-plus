#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


typedef union
{
    int rInt;
    float rFloat;
    char rChar;
} returnData;

typedef struct 
{
    int currentSize;
    int currentTop;
    char vectorDataType;
    union
    {
        int* intData;
        float* floatData;
        char* charData;
    }vectorData;

}vector;





vector* create_vector(int initialSize, char type);
/*
* Creates a vector on the heap with size @param 'initialSize' holding @param 'type'
*   @param    initialSize  - Initial size of the vector
*   @param     type        - Datatype to be held in the vector
*
*   @return   vector*      - Pointer to the vector
*/

bool print_vector(vector * vector);
/*
* Print @param 'vector'
*   @param    vector      - Vector of interest
*
*   @return   bool        - Success/Failure
*/

bool destroy_vector(vector* vector);
/*
* Deallocate @param 'vector' from the heap
*   @param    vector      - Vector of interest
*
*   @return   bool        - Success/Failure
*/

int get_vector_size(vector* vector);
/*
* Returns the amount of used space in a vector
*   @param    vector      - Vector of interest
*
*   @return   int         - Amount of items the vector is holding
*/

int get_vector_memory_size(vector* vector);
/*
* Returns the amount of used space by the vector
*   @param    vector      - Vector of interest
*
*   @return   int         - Amount of items the vector can hold
*/

bool append_vector(vector* vector, void* newData, size_t newDataSize);
/*
* Appends items from @param 'newData' to @param 'vector', enlarging the vector if required
*   @param    vector      - Vector of interest
*   @param    newData     - Array of data to be added to the array
*   @param    newDataSize - Number of elements in @param 'newData'
*
*   @return   bool        - Success/Failure
*/

bool get_index_vector(vector* vector, size_t index, returnData* returnData);
/*
* Returns the data stored at an index @param 'index' in @param 'vector', placing it in @param 'returnData'
*   @param    vector      - Vector of interest
*   @param    index       - Index in vector of interest
*   @param    returnData  - Union of return values
*
*   @return   bool        - Success/Failure
*/

bool set_index_vector(vector* vector, size_t index, void* newData);
/*
* Sets vector @param 'vector' at index @param 'index' to @param 'newData'
*   @param    vector      - Vector of interest
*   @param    index       - Index in vector of interest
*   @param    newData     - Pointer to data of interest
*
*   @return   bool        - Success/Failure
*/

bool offset_vector_size(vector* vector, int offsetSize);
/*
* Changes the size of vector @param 'vector' by increasing or decreasing its size by an offset @param 'offsetSize'
*   @param    vector      - Vector of interest
*   @param    offsetSize  - Size do adjust vector by (can be negative or positive)
*
*   @return   bool        - Success/Failure
*/



