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


void map_print(Map *const map);
bool map_initialise(Map *const map, size_t dataSize, size_t initialMapSize, size_t bucketSize);


#endif // HASHMAP_H



