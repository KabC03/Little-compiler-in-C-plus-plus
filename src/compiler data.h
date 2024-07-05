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


    //Declarations
    TYPE_DECL = 0,
    TYPE_INT = 1,
    TYPE_FLOAT = 2,
    TYPE_CHAR = 3,
    TYPE_EQUALS_ASSIGN = 4,

    //Conditionals
    COND_IF = 5,
    COND_ELIF = 6,
    COND_ELSE = 7,
    COND_WHILE = 8,
    COND_FOR = 9,


    //Organisation
    COMMA = 10,


    //Functions
    FUNC_DECLARE = 11,
    FUNC_RETURN = 12,

    FUNC_FREE = 13,
    FUNC_ALLOCATE = 14,
    FUNC_SIZEOF = 15,


    //Arithmatic symbols
    ARI_PLUS = 16,
    ARI_MINUS = 17,
    ARI_MUL = 18,
    ARI_DIV = 19,
    ARI_MOD = 20,


    //Conditional symbols
    COND_EQUAL_TO = 21,
    COND_NOT_EQUAL_TO = 22,
    COND_GREATER_EQUAL_TO = 23,
    COND_LESS_EQUAL_TO = 24,
    COND_GREATER = 25,
    COND_LESS = 26,


    //Misc symboks



    

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
    ";", "+", "-", "*", "/", "%%", ","

    "(", ")", "[", "]", "{", "}",

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



