#include "compiler data.h"



//Put these into a hashmap in main
const char validTokens[][MAX_KEYWORD_SIZE] = {

    //Declarations
    "int", "float", "char", 
    "=",


    //Conditional statements
    "if", "elif", "else", "while", "for",
    "==", "!=", ">=", "<=",

    //Functions
    "decl", "return", 

    //Organisation
    "$data$", "$function$", "$program$", "//",


    //Inbuilt functions
    "allocate", "free", "sizeof",


    //Misc symbols
    ";", "+", "-", "*", "/", "%%",

    "(", ")", "[", "]", "{", "}", ",", ".",

};

































