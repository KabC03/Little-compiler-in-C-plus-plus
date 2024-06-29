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

extern const char KeyWords[][MAX_KEYWORD_SIZE];

typedef enum TOKEN_TYPE {


    //Declarations    
    DATATYPE,                     //int, float, char
    EQUALS_ASSIGNMENT,            //=

    //Conditional statements
    IF,                           //if
    ELIF,                         //elif
    ELSE,                         //else

    WHILE,                        //while
    FOR,                          //for

    EQ,                           //==
    NEQ,                          //!=
    
    LES,                          //<
    GRE,                          //>
    LTE,                          //<=
    GTE,                          //>=


    //Functions
    DECL,                         //delc (declare function)

    //Organisation
    DATA,                         //$data$
    FUNCTION,                     //$function$
    PROGRAM,                      //$program$
    COMMENT,                      //#

    //Inbuilt functions
    ALLOCATE,                     //allocate()
    FREE,                         //free()
    SIZEOF,                       //sizeof()



    //Misc symbols
    SEMICOLEN,                    //;
    
    ADD,                          //+
    SUB,                          //-
    MUL,                          //*
    DIV,                          ///
    MOD,                          //%

    OPEN_BRACE,                   //(
    CLOSE_BRACE,                  //)
    OPEN_SQUARE,                  //[
    CLOSE_SQUARE,                 //]
    OPEN_CURLY,                   //{
    CLOSE_CURLY,                  //}

    COMMA,                        //,

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






