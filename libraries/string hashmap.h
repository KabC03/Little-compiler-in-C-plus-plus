
//Hashmap for strings (since the other hashmap library doesnt work with them)

#ifndef STRING_HASHMAP_H
#define STRING_HASHMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"
#include "datastructures.h"


typedef struct StringHashmap{

    Vector stringMapListNode;

} StringHashmap;

bool string_hashmap_initialise(StringHashmap *stringHashmap, size_t initialHashmapSize);



#endif // STRING_HASHMAP_H






