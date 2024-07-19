#include "dynamic string.h"








/**
 * dynamic_string_initialise 
 * ===============================================
 * Brief: Initialise a dynamic string 
 * 
 * Param: *dynamicString - string of interest
 * 
 * Return: RETURN_CODE - T/F depending on if addition was successful
 * 
 */
RETURN_CODE dynamic_string_initialise(DynamicString *dynamicString) {

    if(dynamicString == NULL) {
        return _INVALID_ARG_PASS_;
    } else {
        dynamicString->size = 0;
        dynamicString->data = NULL;
    }

    return _SUCCESS_;
}





/**
 * dynamic_string_initialise 
 * ===============================================
 * Brief: Set or reset a dynamic string 
 * 
 * Param: *dynamicString - string of interest
 *        *inputString - String to copy from
 * 
 * Return: RETURN_CODE - T/F depending on if addition was successful
 * 
 */
RETURN_CODE dynamic_string_set(DynamicString *dynamicString, char *inputString) {

    if(dynamicString == NULL || inputString == NULL) {
        return _INVALID_ARG_PASS_;
    } else {

        char *newPtr = realloc(dynamicString->data, strlen(inputString) + 1);
        if(newPtr == NULL) { //Realloc returns NULL if block is unchaged
            return _ALLOC_FAILURE_;
        } else {
            dynamicString->data = newPtr;
        }


        dynamicString->size = strlen(inputString) + 1;
        strncpy(dynamicString->data, inputString, dynamicString->size); 
    }

    return _SUCCESS_;
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
RETURN_CODE dynamic_string_concatanate(DynamicString *dynamicString, char *inputString) {

    if(dynamicString == NULL || inputString == NULL) {
        return _INVALID_ARG_PASS_;
    } else {

        char *newPtr = realloc(dynamicString->data, dynamicString->size + strlen(inputString) + 1);
        if(newPtr == NULL) {
            return _ALLOC_FAILURE_;
        } else {

            dynamicString->data = newPtr;
            dynamicString->size += strlen(inputString) + 1;
            strcat(dynamicString->data, inputString);
        }

    }

    return _SUCCESS_;
}






/**
 * dynamic_string_destroy
 * ===============================================s
 * Brief: Destroy memory associated with a dynamic string 
 * 
 * Param: *dynamicString - string of interest
 *        *inputString - String to copy from
 * 
 * Return: Pointer to the dynamic string 
 * 
 */
RETURN_CODE dynamic_string_destroy(DynamicString *dynamicString) {

    if(dynamicString == NULL) {


        return _INVALID_ARG_PASS_;
    } else {

        if(dynamicString->data == NULL) {

            return _CRITICAL_ERROR_; //Library is not functioning properly if this has happened
        }
        free(dynamicString->data);
    }

    return _SUCCESS_;
}



/*
TODO: add later
- Strcmp
- Strlen
- Strstr
*/






