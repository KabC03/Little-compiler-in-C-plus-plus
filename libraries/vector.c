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
        vector->elementSize = 0;
        vector->size = elementSize;
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
uint8_t* vector_insert_index(Vector *const vector, size_t index, void* data) {


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
uint8_t* vector_delete_index(Vector *const vector, size_t index) {


}
































