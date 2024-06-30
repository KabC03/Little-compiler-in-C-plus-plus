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
#include "hashmap.h"

#define MAX_KEYWORD_SIZE 100
#define MAX_LINE_LENGTH 100

#define MAX_TOKEN_LENGTH 15 //Size of the largest token
#define NUM_KEYWORDS 36 //Number of items in TOKEN_TYPE and KEYWORDS (EXCLUDING DATA)
#define array_length(array) sizeof(array)/sizeof(array[0])


extern const char validTokens[][MAX_KEYWORD_SIZE];




typedef enum TOKEN_TYPE { //NOTE - ORDER CORROSPONDS TO DATA IN COMPILER DATA.c


    //Declarations    
    INT = 0,                           //int
    FLOAT = 1,                         //float
    CHAR = 2,                          //char
    EQUALS_ASSIGNMENT = 3,             //=

    //Conditional statements
    IF = 4,                            //if
    ELIF = 5,                          //elif
    ELSE = 6,                          //else

    WHILE = 7,                         //while
    FOR = 8,                           //for

    EQ = 9,                            //==
    NEQ = 10,                          //!=
    
    LES = 11,                          //<
    GRE = 12,                          //>
    LTE = 13,                          //<=
    GTE = 14,                          //>=


    //Functions
    DECL = 15,                         //delc (declare function)

    //Organisation
    DATA = 16,                         //$data$
    FUNCTION = 17,                     //$function$
    PROGRAM = 18,                      //$program$
    COMMENT = 19,                      //#

    //Inbuilt functions
    ALLOCATE = 20,                     //allocate()
    FREE = 21,                         //free()
    SIZEOF = 22,                       //sizeof()



    //Misc symbols
    SEMICOLEN = 23,                    //;
    
    ADD = 24,                          //+
    SUB = 25,                          //-
    MUL = 26,                          //*
    DIV = 27,                          ///
    MOD = 28,                          //%

    OPEN_BRACE = 29,                   //(
    CLOSE_BRACE = 30,                  //)
    OPEN_SQUARE = 31,                  //[
    CLOSE_SQUARE = 32,                 //]
    OPEN_CURLY = 33,                   //{
    CLOSE_CURLY = 34,                  //}

    COMMA = 35,                        //,
    DOT = 36,                          //.
    

    //DO NOT INCLUDE IN COUNT FOR NUMBER OF WORDS
    //Data - since doesnt have a hashable form - push these down everytime a new hashable word is entered
    INT_IMMEDIATE = 37,                //10
    FLOAT_IMMEDIATE = 38,              //10.2
    CHAR_IMMEDIATE = 39,               //'a'
    VARIABLE = 40,                     //var1


} TOKEN_TYPE;


typedef struct Token {

    TOKEN_TYPE Token;

    //Immediates and variables
    union {
        size_t variableKey;     //Hash into variable hashmap to get the variable name

        char charImmediate;     //Used if immediate char 'f'
        int intImmediate;       //Used for immediate int '3'
        float floatImmediate;   //Used for immediate float '3.32'
    };


} Token;




#endif // COMPILE_H 






