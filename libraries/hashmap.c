#include "hashmap.h"

#define DJB2_CONSTANT 5381


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




