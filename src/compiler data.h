// Compiler data

#ifndef COMPILE_H 
#define COMPILE_H 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"
#include "datastructures.h"
#include "static hashmap.h"

#define MAX_KEYWORD_SIZE 100
#define MAX_LINE_LENGTH 100

#define MAX_TOKEN_LENGTH 20 //Size of the largest token
#define NUM_KEYWORDS 34 //Number of items in TOKEN_TYPE and KEYWORDS (EXCLUDING DATA)
#define VARIABLE_HASHMAP_SIZE 100 //Size of array hashmap initially
#define array_length(array) sizeof(array)/sizeof(array[0])




//Tokenser structures
extern const char validTokens[][MAX_KEYWORD_SIZE];



typedef enum TOKEN_TYPE { //NOTE - ORDER CORROSPONDS TO DATA IN COMPILER DATA.c

    //DO NOT INCLUDE IN COUNT FOR NUMBER OF WORDS
    //Data - since doesnt have a hashable form - push these down everytime a new hashable word is entered
    INT_IMMEDIATE = -6,                //10
    FLOAT_IMMEDIATE = -5,              //10.2
    CHAR_IMMEDIATE = -4,               //'a'
    USER_VARIABLE_STRING = -3,         //var1, function names
    USER_STRING = -2,                  //User string (could be keyword, function name or variable name)    
    INVALID = -1,                      //invalid token



    DECL_DECL = 0,
    DECL_INT = 1,
    DECL_FLOAT = 2,
    DECL_CHAR = 3,
    DECL_EQUALS = 4,

    COND_IF = 5,
    COND_ELIF = 6,
    COND_ELSE = 7,
    COND_WHILE = 8,
    COND_FOR = 9,

    COMP_EQUAL_TO = 10,
    COMP_NOT_EQUAL_TO = 11,
    COMP_GREATER_EQUAL_TO = 12,
    COMP_LESS_EQUAL_TO = 13,
    COMP_GREATER = 14,
    COMP_LESS = 15,

    FUNC_DECL = 16,
    FUNC_RETURN = 17,

    COMMENT = 18,
    

    INBUILT_ALLOCATE = 19,
    INBUILT_FREE = 20,
    INBUILT_SIZEOF = 21,

    MISC_SEMICOLON = 22,
    ARI_PLUS = 23,
    ARI_MINUS = 24,
    ARI_MUL = 25,
    ARI_DIV = 26,
    ARI_MOD = 27,
    MISC_COMMA = 28,


    OPEN_PARAN = 29,
    CLOSE_PARAN = 30,
    OPEN_SQUARE = 31,
    CLOSE_SQUARE = 32,
    OPEN_CURLEY = 33,
    CLOSE_CURLEY = 34,

} TOKEN_TYPE;


typedef struct Token {

    TOKEN_TYPE Token;

    //Immediates and variables
    union {
        char *userString;        //User string (func name, variable, etc - parser must determine based on context)

        char charImmediate;     //Used if immediate char 'f'
        int intImmediate;       //Used for immediate int '3'
        float floatImmediate;   //Used for immediate float '3.32'
    };


} Token;


#endif // COMPILE_H 



