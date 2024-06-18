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



#endif // HASHMAP_H



