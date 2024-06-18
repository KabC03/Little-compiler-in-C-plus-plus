#include "hashmap.h"



struct MapNode {

    Vector value;
};


void cleanup(Map *map) {

    if(map == NULL) {
        return;
    } else {

        for(int i = 0; i <= vector_get_length(&(map->mapNodes)); i++) {

            vector_destroy(vector_get_index(&(map->mapNodes), i));
        }
    }
    vector_destroy(&(map->mapNodes));

    return;
}


bool map_initialise(Map *const map, size_t dataSize, size_t initialMapSize, size_t bucketSize) {

    if(map == NULL || dataSize == 0 || initialMapSize == 0 || bucketSize == 0) {
        return false;
    }
    
    if(vector_initialise(&(map->mapNodes), sizeof(MapNode)) == false) {
        return false;
    }

    if(vector_resize(&(map->mapNodes), initialMapSize) == false) {
        vector_destroy(&(map->mapNodes));
        return false;
    }
    
    for(int i = 0; i < initialMapSize; i++) {


        if(vector_initialise(vector_get_index(&(map->mapNodes), i), dataSize) == false) {

        }
        if(vector_resize(vector_get_index(&(map->mapNodes), i), bucketSize) == false) {

        }
    }


    return true;
}



























