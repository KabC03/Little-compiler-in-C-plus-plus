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
 * string_hashmap_print
 * ===============================================
 * Brief: Print a string hashmap (used for debugging)
 * 
 * Param: *data - Data to hash
 * 
 * Return: bool - T/F depending on if freeing was successful
 * 
 */
bool string_hashmap_print(StringHashmap *stringHashmap) {

    if(stringHashmap == NULL) {
        return false;
    } else {

        size_t tableSize = vector_get_size(&(stringHashmap->stringMapListNode)) + 1;

        for(size_t i = 0; i < tableSize; i++) {

            printf("            Bucket: %zu:\n",i);
            StringMapList *listToInsertTo = (StringMapList*)vector_get_index(&(stringHashmap->stringMapListNode), i);

            string_map_LL_print(listToInsertTo);
        }
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

        if(vector_initialise(&(stringhashmap->stringMapListNode), sizeof(StringMapList)) == false) {

            return false;
        }
        
        if(vector_resize(&(stringhashmap->stringMapListNode), initialHashmapSize) == false) {
            vector_destroy(&(stringhashmap->stringMapListNode));

            return false;
        }




        StringMapList newMap;
        if(string_map_LL_initilise(&newMap) == false) {
            vector_destroy(&(stringhashmap->stringMapListNode));

            return false;
        }

        for(size_t i = 0; i < initialHashmapSize; i++) {
            //vector_get_index can return null ptr but map_LL will notice it

            if(vector_insert_index(&(stringhashmap->stringMapListNode), i, &newMap) == false) {
                for(int j = 0; j < i; j++) {
                    string_map_LL_destroy((StringMapList*)vector_get_index(&(stringhashmap->stringMapListNode), i));
                }

                //vector_destroy(&(hashmap->mapListNodes)); //CAUSES ERROR - BUT SHOULD BE HERE TO AVOID LEAKS
                return false;
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
        size_t tableSize = vector_get_size(&(stringHashmap->stringMapListNode)) + 1;

        if(string_hashmap_hash(key, keySize, tableSize, &hashIndex) == false) {
            return false;
        }


        StringMapList *listToInsertTo = (StringMapList*)vector_get_index(&(stringHashmap->stringMapListNode), hashIndex);

        if(string_map_LL_set(listToInsertTo, key, value, keySize, valueSize) == false) {
            return false;
        }


    }

    return true;
}






/**
 * string_hashmap_get_value
 * ===============================================
 * Brief: Get a value from a hashmap for a given key 
 * 
 * Param: *stringhashmap - Hashmap to initialise
 *        *key - Key to add to the hashmap
 *        keySize - Size of the added key
 * 
 * Return: Constant void pointer to data 
 * 
 */
const void *string_hashmap_get_value(StringHashmap *stringHashmap, void *key, size_t keySize) {

    if(stringHashmap == NULL || key == NULL || keySize == 0) {

        return NULL;
    } else {

        size_t hashIndex = -1;
        size_t tableSize = vector_get_size(&(stringHashmap->stringMapListNode)) + 1;

        if(string_hashmap_hash(key, keySize, tableSize, &hashIndex) == false) {
            return false;
        }


        StringMapList *listToInsertTo = (StringMapList*)vector_get_index(&(stringHashmap->stringMapListNode), hashIndex);


        const void *returnPtr = string_map_LL_get_value(listToInsertTo, key, keySize);

        return returnPtr;
    }
    
    return NULL;
}


