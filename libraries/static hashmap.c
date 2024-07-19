#include "static hashmap.h"

#define DJB2_CONSTANT 5381
#define hashmap_hash_djb2 hashmap_hash //Do this to select the current hash algorithm

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



/*
TODO:

- Initialise hashmap
- Add to hashmap
- Remove from hashmap
- Get value
- Destroy hashmap
*/


/**
 * hashmap_print
 * ===============================================
 * Brief: Print a hashmap of ints - used for debugging
 * 
 * Param: *hashmap - Hashmap of interest 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_print(HashMap *const hashmap) {

    if(hashmap == NULL) {
        return false;
    } else {

        for(int i = 0; i < vector_get_length(&(hashmap->mapListNodes)) + 1; i++) {
            printf("Bucket: %d\n",i);
            map_LL_print((MapList*)(vector_get_index(&(hashmap->mapListNodes), i)));
            
        }   
    }

    return true;
}




/**
 * hashmap_initiahlise 
 * ===============================================
 * Brief: Initialise a hash table 
 * 
 * Param: *hashmap - Hashmap of interest 
 *        keySize - Size of keys
 *        TableSize - Table size
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_initialise(HashMap *const hashmap, size_t keySize, size_t valueSize, size_t TableSize) {

    if(hashmap == NULL || keySize == 0 || valueSize == 0 || TableSize == 0) {
        return false;
    } else {


        hashmap->keySize = keySize;
        hashmap->valueSize = valueSize;
        if(vector_initialise(&(hashmap->mapListNodes), sizeof(MapList)) == false) {
            return false;
        }
        
        if(vector_resize(&(hashmap->mapListNodes), TableSize) == false) {
            vector_destroy(&(hashmap->mapListNodes));
            return false;
        }




        MapList newMap;
        if(map_LL_initialise(&newMap) == false) {
            vector_destroy(&(hashmap->mapListNodes));
            return false;
        }

        for(size_t i = 0; i < TableSize; i++) {
            //vector_get_index can return null ptr but map_LL will notice it

            if(vector_insert_index(&(hashmap->mapListNodes), i, &newMap) == false) {
                for(int j = 0; j < i; j++) {
                    map_LL_destroy((MapList*)vector_get_index(&(hashmap->mapListNodes), i));
                }
                
                //vector_destroy(&(hashmap->mapListNodes)); //CAUSES ERROR - BUT SHOULD BE HERE TO AVOID LEAKS
                return false;
            }
        
        } 

    }

    return true;
}


/**
 * hashmap_insert
 * ===============================================
 * Brief: Insert into a hashtable or reset a value
 * 
 * Param: *hashmap - Hashmap of interest 
 *        *key - key of interest to insert
 *        *value - Corrosponding value to insert
 *        keySize - keySize (0 to use default)
 *        valueSize - valueSize (0 to use default)
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_insert(HashMap *const hashmap, void *const key, void *const value) {

    if(hashmap == NULL || key == NULL || value == NULL) {
        return false;
    } else {

        //Hash the key
        size_t hash = 0;
        size_t tableSize = vector_get_size(&(hashmap->mapListNodes)) + 1; //get_size returns zero based index
        if(tableSize == 0) {
            return false;
        }
        if(hashmap_hash(key, hashmap->keySize, tableSize, &hash) == false) {
            return false;
        } 
        
        if(map_LL_insert_front((MapList*)vector_get_index(&(hashmap->mapListNodes), hash), key, value, hashmap->keySize, hashmap->valueSize) == false) {
            return false;
        }

    }

    return true;
}



/**
 * hashmap_get_value
 * ===============================================
 * Brief: Get a value from a hashmap
 * 
 * Param: *hashmap - Hashmap of interest 
 *        *key - key of interest to insert
 *        *valueOut - Output of hash table 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_get_value(HashMap *const hashmap, void *const key, const void **valueOut) {

    if(hashmap == NULL || key == NULL || valueOut == NULL) {
        return false;
    } else {

        //Hash the key
        size_t hash = 0;
        size_t tableSize = vector_get_size(&(hashmap->mapListNodes)) + 1; //get_size returns zero based index
        
         
        if(tableSize == 0) {
            return false;
        }
        if(hashmap_hash(key, hashmap->keySize, tableSize, &hash) == false) {
            return false;
        }
        
        
        *valueOut = map_LL_get_value((MapList*)vector_get_index(&(hashmap->mapListNodes), hash), key, hashmap->keySize);
    }


 


    return true;
}



/**
 * hashmap_remove
 * ===============================================
 * Brief: Remove a key/value from a hashmap
 * 
 * Param: *hashmap - Hashmap of interest 
 *        *key - key of interest to delete
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_remove(HashMap *const hashmap, void *const key) {

    if(hashmap == NULL || key == NULL) {
        return false;
    } else {

        //Hash the key
        size_t hash = 0;
        size_t tableSize = vector_get_size(&(hashmap->mapListNodes)) + 1; //get_size returns zero based index
        
         
        if(tableSize == 0) {
            return false;
        }
        if(hashmap_hash(key, hashmap->keySize, tableSize, &hash) == false) {
            return false;
        }


        if(map_LL_delete_key((MapList*)vector_get_index(&(hashmap->mapListNodes), hash), key, hashmap->keySize) == false) {
            return false;
        }
    }


    return true;
}



/**
 * hashmap_destroy
 * ===============================================
 * Brief: Destroy a hashmap
 * 
 * Param: *hashmap - Hashmap of interest 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_destroy(HashMap *const hashmap) {

    if(hashmap == false) {
        return false;
    } else {

        size_t mapSize = 0;
        if(vector_get_size(&(hashmap->mapListNodes)) == false) {
            return false;
        }


        for(size_t i = 0; i < mapSize; i++) {
            if(map_LL_destroy((MapList*)vector_get_index(&(hashmap->mapListNodes), i)) == false) {
                return false;
            }
        }
        vector_destroy(&(hashmap->mapListNodes));
    }

    return true;
}



