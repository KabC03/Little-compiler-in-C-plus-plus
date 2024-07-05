#include "compiler data.h"



//Put these into a hashmap in main
const char validTokens[NUM_KEYWORDS][MAX_KEYWORD_SIZE] = {

    //Declarations
    "decl", "int", "float", "char", 
    "=",


    //Conditional statements
    "if", "elif", "else", "while", "for",
    "==", "!=", ">=", "<=", ">", "<"

    //Functions
    "fn", "return", 

    //Organisation
    "//"

    //Inbuilt functions
    "allocate", "free", "sizeof",

    //Misc symbols
    ";", "+", "-", "*", "/", "%%", ",",

    "(", ")", "[", "]", "{", "}",

};




 
