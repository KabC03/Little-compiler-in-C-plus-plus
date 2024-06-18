#include "hashmap.h"



struct MapNode {

    Vector value;
};


/**
 * map_print
 * =========================
 * Brief: Prints a map of integers (used for debugging)
 * Param: *map - Map to be printed
 * 
 * Return: void
 */
void map_print(Map *const map) {

    if(map == NULL) {
        return;
    }


    for(size_t i = 0; i <= vector_get_length(&(map->mapNodes)); i++) {

        vector_print((Vector*)vector_get_index((Vector*)(&((map->mapNodes))), i));
    }

    return;
}



void cleanup(Map *map) {

    if(map == NULL) {
        return;
    } else {

        for(size_t i = 0; i <= vector_get_length(&(map->mapNodes)); i++) {

            vector_destroy((Vector*)vector_get_index((Vector*)(&((map->mapNodes))), i));
        }
    }
    vector_destroy((Vector*)(&((map->mapNodes))));

    return;
}

/**
 * map_initialise
 * =========================
 * Brief: Initialises a map
 * Param: *map - Map to be initialised
 *      dataSize - Size of the data in the map (e.g sizeof(int))
 *      initialMapSize - Initial size of the map
 *      bucketSize - number of initial expected collisions
 * Return: T/F depending on if initialisation was successful
 */
bool map_initialise(Map *const map, size_t dataSize, size_t initialMapSize, size_t bucketSize) {

    if(map == NULL || dataSize == 0 || initialMapSize == 0 || bucketSize == 0) {
        return false;
    }
    
    if(vector_initialise(&(map->mapNodes), sizeof(MapNode)) == false) {
        return false;
    }

    if(vector_resize((Vector*)&((map->mapNodes)), initialMapSize) == false) {
        vector_destroy(&(map->mapNodes));
        return false;
    }
    
    for(int i = 0; i < initialMapSize; i++) {


        if(vector_initialise((Vector*)vector_get_index(&(map->mapNodes), i), dataSize) == false) {

        }
        if(vector_resize((Vector*)vector_get_index(&(map->mapNodes), i), bucketSize) == false) {

        }
    }


    return true;
}



























