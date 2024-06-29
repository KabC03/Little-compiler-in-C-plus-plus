//Hashmap in C - allows collisions

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"
#include "datastructures.h"


typedef struct HashMap {
 
    Vector mapListNodes;
    size_t keySize;
    size_t valueSize;

} HashMap;



bool hashmap_hash_djb2(const uint8_t *const data, size_t dataSize, size_t tableSize, size_t *const hashOut); 
bool hashmap_print(HashMap *const hashmap);
bool hashmap_initialise(HashMap *const hashmap, size_t keySize, size_t valueSize, size_t TableSize);
bool hashmap_insert(HashMap *const hashmap, void *const key, void *const value);
bool hashmap_get_value(HashMap *const hashmap, void *const key, const void **valueOut);
bool hashmap_remove(HashMap *const hashmap, void *const key);
bool hashmap_destroy(HashMap *const hashmap);

#endif // HASHMAP_H
