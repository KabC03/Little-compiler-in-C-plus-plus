
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


bool string_hashmap_print(StringHashmap *stringHashmap);
bool string_hashmap_initialise(StringHashmap *stringHashmap, size_t initialHashmapSize);
bool string_hashmap_set(StringHashmap *stringHashmap, void *key, size_t keySize, void *value, size_t valueSize);
const void *string_hashmap_get_value(StringHashmap *stringHashmap, void *key, size_t keySize);

#endif // STRING_HASHMAP_H



