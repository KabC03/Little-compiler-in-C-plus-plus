#include "dynamic string.h"








/**
 * dynamic_string_initialise 
 * ===============================================
 * Brief: Initialise a dynamic string 
 * 
 * Param: *dynamicString - string of interest
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
bool dynamic_string_initialise(DynamicString *dynamicString) {

    if(dynamicString == NULL) {
        return false;
    } else {

        dynamicString->size = 0;
        dynamicString->data = NULL;
    }

    return true;
}





/**
 * dynamic_string_initialise 
 * ===============================================
 * Brief: Set or reset a dynamic string 
 * 
 * Param: *dynamicString - string of interest
 *        *inputString - String to copy from
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
bool dynamic_string_set(DynamicString *dynamicString, char *inputString) {

    if(dynamicString == NULL || inputString == NULL) {
        return false;
    } else {

        char *newPtr = realloc(dynamicString->data, strlen(inputString) + 1);
        if(newPtr == NULL) { //Realloc returns NULL if block is unchaged
            return false;
        } else {
            dynamicString->data = newPtr;
        }


        dynamicString->size = strlen(inputString) + 1;
        strncpy(dynamicString->data, inputString, dynamicString->size); 
    }

    return true;
}




/**
 * dynamic_string_read 
 * ===============================================s
 * Brief: Read from a dynamic string 
 * 
 * Param: *dynamicString - string of interest
 *        *inputString - String to copy from
 * 
 * Return: Pointer to the dynamic string 
 * 
 */
const char *dynamic_string_read(const DynamicString *dynamicString) {

    if(dynamicString == NULL) {
        return NULL;
    } else {
        return dynamicString->data; 
    }


    return NULL; //Put this here so the compiler doesnt complain 
}





/**
 * dynamic_string_concatanate 
 * ===============================================s
 * Brief: Concatanate a dynamic string with another 
 * 
 * Param: *dynamicString - string of interest
 *        *inputString - String to add 
 * 
 * Return: Pointer to the dynamic string 
 * 
 */
bool dynamic_string_concatanate(DynamicString *dynamicString, char *inputString) {

    if(dynamicString == NULL || inputString == NULL) {
        return false;
    } else {

        char *newPtr = realloc(dynamicString->data, dynamicString->size + strlen(inputString) + 1);
        if(newPtr == NULL) {
            return false;
        } else {

            dynamicString->data = newPtr;
            dynamicString->size += strlen(inputString) + 1;
            strcat(dynamicString->data, inputString);
        }

    }

    return true;
}

/*
TODO: add later
- Compare strings (stcmp)
- And so on
*/






























