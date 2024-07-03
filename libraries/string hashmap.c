#include "string hashmap.h"





/**
 * string_hashmap_initialise 
 * ===============================================
 * Brief: Initialise a dynamic hashmap 
 * 
 * Param: *stringhashmap - Hashmap to initialise
 *        initialhashmapSize - Initial size of the hashmap
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool string_hashmap_initialise(StringHashmap *stringhashmap, size_t initialHashmapSize) {
    
    if(stringhashmap == NULL || initialHashmapSize == 0) {
        return false;
    } else {


        //Initialise hashmap vector
        if(vector_initialise(&(stringhashmap->stringMapListNode), sizeof(StringMapListNode)) == false) {
            return false;
        }

        //Resize vector
          

        //Initialise LL in hashmap vector
        for(size_t i = 0; i < initialHashmapSize; i++) {

        }

    }
    
    return true;
}







































