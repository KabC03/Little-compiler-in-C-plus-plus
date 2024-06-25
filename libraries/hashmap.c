#include "hashmap.h"

#define DJB2_CONSTANT 5381


/**
 * hashmap_hash_djb2
 * ===============================================
 * Brief: Perform a djb2 hash
 * 
 * Param: *data - Data to hash
 *        dataSize - Size of data to hash
 *        tableSize - Size of the table
 *        *hashOut - Hash output
 * 
 * Return: bool - T/F depending on if freeing was successful
 * 
 */
bool hashmap_hash_djb2(const uint8_t *const data, size_t dataSize, size_t tableSize, size_t *const hashOut) {

    size_t hash= DJB2_CONSTANT;
    if(data == NULL || dataSize == 0) {
        return false;
    } else {

        for(size_t i = 0; i < dataSize; i++) {
            
            hash = (hash << 5) + hash + data[i];

        }    
        hash %= tableSize;
        *hashOut = hash;
    }
    return true;
}



/*
TODO:

- Initialise hashmap
- Add to hashmap
- Remove from hashmap
- Get value
- Destroy hashmap
*/

/**
 * hashmap_initiahlise 
 * ===============================================
 * Brief: Initialise a hash table 
 * 
 * Param: *hashmap - Hashmap of interest 
 *        keySize - Size of keys
 *        initialTableSize - Initial table size
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_initialise(HashMap *const hashmap, size_t keySize, size_t valueSize, size_t initialTableSize) {

    if(hashmap == NULL || keySize == 0 || valueSize == 0 || initialTableSize == 0) {
        return false;
    } else {

        if(vector_initialise(&(hashmap->mapListNodes), sizeof(MapList)) == false) {
            return false;
        }
        
        if(vector_resize(&(hashmap->mapListNodes), initialTableSize) == false) {
            return false;
        }

        for(size_t i = 0; i < initialTableSize; i++) {
            //vector_get_index can return null ptr but map_LL will notice it
            if(map_LL_initialise((MapList*)vector_get_index(&(hashmap->mapListNodes), i), keySize, valueSize) == false) {
                return false;
            }

        }

    }

    return true;
}









