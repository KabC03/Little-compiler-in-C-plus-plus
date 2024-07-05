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

#define MAX_TOKEN_LENGTH 15 //Size of the largest token
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


    //Variable assignment
    TYPE_VARIABLE_DECL = 0,
    TYPE_INT = 1,
    TYPE_FLOAT = 2,
    TYPE_CHAR = 3,
    EQUALS_ASSIGNMENT = 4,

    //Arithmatic operators
    ARITH_PLUS = 5,
    ARITH_MINUS = 6,
    ARITH_MULTIPLY = 7,
    ARITH_DIVIDE = 8,
    ARITH_MODULO = 9,

    //Conditional statements
    IF = 10,
    ELIF = 11,
    ELSE = 12,
    WHILE = 13,
    FOR = 14,

    //Conditional operators
    COND_EQUAL_TO = 15,
    COND_NOT_EQUAL_TO = 16,
    COND_GREATER_OR_EQUAL_TO = 17,
    COND_LESS_OR_EQUAL_TO = 18,
    COND_GREATER_THAN = 19,
    COND_LESS_THAN = 20,


    //Functions
    FUNCT_DECLARE = 21,    //fn
    FUNCT_RETURN = 22,     //return


    //Organisation
    COMMENT = 23,


    //Inbuilt functions
    INBUILT_ALLOCATE = 24,
    INBUILT_FREE = 25,
    INBUILT_SIZEOF = 26,


    //Brackets
    OPEN_PAREN = 27,
    CLOSE_PAREN = 28,
    OPEN_SQUARE = 29,
    CLOSE_SQUARE = 30,
    OPEN_CURLEY = 31,
    CLOSE_CURLEY = 32, 


    //Other symbols
    SEMICOLEN = 33,

    //Note that '.' is not here since its used in decimals - tokeniser will disguard so dont put it here


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






