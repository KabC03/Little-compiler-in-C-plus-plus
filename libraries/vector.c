#include "vector.h"

/**
 * vector_get_size
 * ===============================================
 * Brief: Gets the size (in bytes) of a vector
 * 
 * Param: *vector - Pointer to the vector of interest
 * Return: size_t - Size of a vector in bytes
 * 
 */
size_t vector_get_size(Vector *vector) {


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
 * Brief: Gets the len of a vector in bytes
 * 
 * Param: *vector - Pointer to the vector of interest
 * Return: size_t - Size of a vector in bytes
 * 
 */














































