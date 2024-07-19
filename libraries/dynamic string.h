//Memory safe dynamic strings in C - meant to be used so no malloc have to appear in the code in relation to a string

#ifndef DYNAMIC_STRING_H 
#define DYNAMIC_STRING_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "return codes.h"


typedef struct DynamicString {

    char *data;
    size_t size; //Size including NULL terminator

} DynamicString;


RETURN_CODE dynamic_string_initialise(DynamicString *dynamicString);
RETURN_CODE dynamic_string_set(DynamicString *dynamicString, char *inputString);
const char *dynamic_string_read(const DynamicString *dynamicString);
RETURN_CODE dynamic_string_concatanate(DynamicString *dynamicString, char *inputString);
RETURN_CODE dynamic_string_destroy(DynamicString *dynamicString);



#endif // DYNAMIC_STRING_H
      
      
      
      
      
      
      
      
