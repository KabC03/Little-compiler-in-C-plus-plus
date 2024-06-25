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

} HashMap;


bool hashmap_hash_djb2(const uint8_t *const data, size_t dataSize, size_t tableSize, size_t *const hashOut); 
bool hashmap_initialise(HashMap *const hashmap, size_t keySize, size_t valueSize, size_t initialTableSize);

#endif // HASHMAP_H


