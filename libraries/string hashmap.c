#include "string hashmap.h"

#define STRING_DJB2_CONSTANT 5381
#define string_hashmap_hash_djb2 string_hashmap_hash //Do this to select the current hash algorithm

/**
 * string_hashmap_hash_djb2
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
bool string_hashmap_hash_djb2(const uint8_t *const data, size_t dataSize, size_t tableSize, size_t *const hashOut) {

    size_t hash= STRING_DJB2_CONSTANT;
    if(data == NULL || dataSize == 0 || hashOut == NULL) {
        return false;
    } else {

        for(size_t i = 0; i < dataSize; i++) {
            
            hash = (hash << 5) + hash + data[i];

        }    
        hash %= tableSize;
        //printf("Recieved: %d || Hash: %zu\n", *(int*)data, hash);
        *hashOut = hash;
    }
    return true;
}


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





/**
 * string_hashmap_set 
 * ===============================================
 * Brief: Set a value in a hashmap given a key
 * 
 * Param: *stringhashmap - Hashmap to initialise
 *        *key - Key to add to the hashmap
 *        keySize - Size of the added key
 *        *value - Value to add to the hashmap
 *        valueSize - Size of the added value to the hashmap
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool string_hashmap_set(StringHashmap *stringHashmap, void *key, size_t keySize, void *value, size_t valueSize) {
    if(stringHashmap == NULL || key == NULL || value == NULL || keySize == 0 || valueSize == 0) {
        
        return false;
    } else {

        size_t hashIndex = -1;
        
        if(string_hashmap_hash(key, keySize, vector_get_size(&(stringHashmap->stringMapListNode)), &hashIndex) == false) {
            return false;
        }

        if(string_map_LL_set((StringMapList*)(vector_get_index(&(stringHashmap->stringMapListNode), hashIndex)),
        key, value, keySize, valueSize) == false) {
            return false;
        }
    }

    return true;
}



































