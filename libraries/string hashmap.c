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
        if(vector_resize(&(stringhashmap->stringMapListNode), initialHashmapSize) == false) {
            return false;
        }

        //Initialise LL in hashmap vector
        
        StringMapList newNode;

        if(string_map_LL_initilise(&newNode) == false) {
            vector_destroy(&(stringhashmap->stringMapListNode));
            return false;
        }


        for(size_t i = 0; i < initialHashmapSize; i++) {

            if(string_map_LL_initilise((StringMapList*)vector_get_index(&(stringhashmap->stringMapListNode), i))) {
                for(size_t j = 0; j < i; j++) {
                    string_map_LL_destroy((StringMapList*)vector_get_index(&(stringhashmap->stringMapListNode), j));
                    return false;
                }
            }
        }
    }
    
    return true;
}







































