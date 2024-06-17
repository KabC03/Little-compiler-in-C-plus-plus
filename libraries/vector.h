#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>



#define Vector(type, name)\
    Vector name;\
    vector_initialise(&name, sizeof(type));\

typedef struct Vector {

    size_t size;         //Memory of vector (num of bytes)

    size_t top;          //Top index of array (index)

    uint8_t* data;       //Data array pointer
    size_t elementSize;  //Size of individual element in array

} Vector;


bool vector_initialise(Vector *const vector, size_t elementSize);
size_t vector_get_size(const Vector *const vector);
size_t vector_get_length(const Vector *const vector);


uint8_t* vector_get_index(Vector *const vector, size_t index);
uint8_t* vector_insert_index(Vector *const vector, size_t index, void* data);
bool vector_delete_index(Vector *const vector, size_t index);
bool vector_resize(Vector *const vector, size_t newSize);
































































