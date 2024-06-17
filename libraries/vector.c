#include "vector.h"





/**
 * vector_get_size
 * ===============================================
 * Brief: Gets the size (in bytes) of a vector
 * 
 * Param: *vector - Pointer to the vector of interest
 *        elementSize - sizeof(element) in bytes
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool vector_initialise(Vector *const vector, size_t elementSize) {

    if(vector == NULL) {
        return false;
    } else {

        vector->data = NULL;
        vector->elementSize = elementSize;
        vector->size = 0;
        vector->top = 0;
    }

    return true;
}



/**
 * vector_get_size
 * ===============================================
 * Brief: Gets the size (in bytes) of a vector
 * 
 * Param: *vector - Pointer to the vector of interest
 * Return: size_t - Size of a vector in bytes
 * 
 */
size_t vector_get_size(const Vector *const vector) {


    size_t size = 0;
    if(vector == NULL) {
        
        return 0;

    } else {

        size = vector->size;

    }
    return size;
}


/**
 * vector_get_len
 * ===============================================
 * Brief: Gets the length of the vector (zero based indexing)
 * 
 * Param: *vector - Pointer to the vector of interest
 * Return: size_t - Size of a vector in bytes
 * 
 */
size_t vector_get_length(const Vector *const vector) {

    size_t length = 0;
    if(vector == NULL) {
        return 0;
    } else {
        length = vector->top;
    }

    return length;
}





/**
 * vector_get_index
 * ===============================================
 * Brief: Returns a pointer to an item in a vector (zero based indexing)
 * 
 * Param: *vector - Pointer to the vector of interest
 *        index - Index of interest
 * Return: uint8_t - Pointer to data within the vector
 * 
 */
uint8_t* vector_get_index(Vector *const vector, size_t index) {

    uint8_t *result = NULL;
    if(vector == NULL) {
        return NULL;
    } else {

        if(index > vector->top || vector->data == NULL) {
            return NULL;
        } else {

            result = &((vector->data)[index * vector->elementSize]);
        }
    }

    return result;
}


/**
 * vector_insert_index
 * ===============================================
 * Brief: Insert an item at an index in the vector (zero based indexing)
 * 
 * Param: *vector - Pointer to the vector of interest
 *        index - Index of interest
 *        *data - Pointer to data to be inserted
 * Return: bool - T/F depending on if insertion was successful
 * 
 */
bool vector_insert_index(Vector *const vector, size_t index, void* data) {


    if(vector == NULL || data == NULL) {
        return false;
    } else if(vector->data == NULL) {
        return false;
    } else {



        if(index > vector->top + 1 || vector->top + 1 > (vector->size)/(vector->elementSize)) { 

            //top is the INDEX of the top element, size is the NUMBER OF BYTES in the array
            return false; //OOB error
            
        } else {
            for(int i = vector->top; i < index; i--) {
                memcpy(&(vector->data)[(i * vector->elementSize) + 1], &(vector->data)[(i*vector->elementSize)], vector->elementSize);
            }

            memcpy(&(vector->data)[index * vector->elementSize], data, vector->elementSize);
        }
        vector->top++;
    }
    return true;
}






/**
 * vector_delete_index
 * ===============================================
 * Brief: Delete an item from the vector (zero based indexing)
 * 
 * Param: *vector - Pointer to the vector of interest
 *        index - Index of interest
 * Return: bool - T/F depending on if deletion was successful
 * 
 */
bool vector_delete_index(Vector *const vector, size_t index) {

    if(vector == NULL) {
        return false;

    } else if(vector->data == NULL) {
        return false;

    } else {



        if(index > vector->top + 1 || vector->top + 1 > (vector->size)/(vector->elementSize)) { 
            //top is the INDEX of the top element, size is the NUMBER OF BYTES in the array

            return false; //OOB error
            
        } else {


            for(int i = 0; i < vector->top; i++) {
                memcpy(&(vector->data)[(i * vector->elementSize)], &(vector->data)[(i*vector->elementSize) + 1], vector->elementSize);
            }

        }
        vector->top--;
    }
    return true;
}



/**
 * vector_resize
 * ===============================================
 * Brief: Resize a vector by expanding or shrinking it (zero based indexing)
 * 
 * Param: *vector - Pointer to the vector of interest
 *        offsetSize - Offset of new size
 * Return: bool - T/F depending on if resize was successful
 * 
 */
bool vector_resize(Vector *const vector, size_t offsetSize) {

    if(vector == NULL) {
        return false;
    } else if(vector->size + offsetSize <= 0) {

        return false;

    } else {

        size_t tempSize = vector->size;

        vector->size = (vector->size + offsetSize ) * vector->elementSize;
        vector->data = realloc(vector->data, (vector->size + offsetSize ) * vector->elementSize);


        if(vector->data == NULL) {
            vector->size = tempSize; //Set size back
            return false;
        }

    }
    return true;
}





























