
//Hashmap for strings (since the other hashmap library doesnt work with them)

#ifndef DYNAMIC_HASHMAP_H 
#define DYNAMIC_HASHMAP_H 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"
#include "datastructures.h"

typedef struct StringHashmapNode {

    size_t keyLength;          //Key string size
    size_t valueLength;        //Value string size
    MapListNode mapListNode;   //Map nodes

} StringHashmapNode;


typedef struct StringHashmap{

    Vector stringHashmapNode;  //Vector of string hashmap nodes 

} StringHashmap;






bool string_hashmap_initialise(StringHashmap *stringHashmap, size_t initialHashmapSize);



#endif // DYNAMIC_HASHMAP_H 






