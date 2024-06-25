//Hashmap in C - allows collisions

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"

typedef struct MapNode MapNode;

typedef struct Map {
    Vector mapNodes;        //Vector of mapnodes
} Map;


bool hashmap_hash_djb2(const uint8_t *const data, size_t dataSize, size_t tableSize, size_t *const hashOut); 

#endif // HASHMAP_H


