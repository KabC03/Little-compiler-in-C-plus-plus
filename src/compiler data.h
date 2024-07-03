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
#define NUM_KEYWORDS 36 //Number of items in TOKEN_TYPE and KEYWORDS (EXCLUDING DATA)
#define VARIABLE_HASHMAP_SIZE 100 //Size of array hashmap initially
#define array_length(array) sizeof(array)/sizeof(array[0])




//Tokenser structures
extern const char validTokens[][MAX_KEYWORD_SIZE];



typedef enum TOKEN_TYPE { //NOTE - ORDER CORROSPONDS TO DATA IN COMPILER DATA.c

    USER_STRING = -2,                  //User string (could be keyword, function name or variable name)    
    INVALID = -1,                      //invalid token

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
    USER_VARIABLE_STRING = 40,         //var1, function names


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



//Parser structures


typedef struct ExpressionTreeNode {

    Token left;
    Token operator;
    Token right;

} ExpressionTreeNode;


typedef struct DeclarationTree {

    Token datatype;                          //e.g int, float, char
    Token variableName;                      //e.g x, var1
    Token equals;                            //=
    ExpressionTreeNode assignedExpression;   //e.g 1 + 2 + (3+2) (NOTE: x == 1 IS AN EXPRESSION THAT RETURNS A VALUE)

} DeclarationTree;


typedef struct IfTree { //Also used for elif, else

    ExpressionTreeNode *expression;          //Pointer to array of expressions
    Token *operator;                         //Corrosponds to above statements (||, &&, etc)

} IfTree;


typedef struct WhileTree { 

    IfTree ifTree;                           //Same as an if tree but with a jump

} WhileTree;


typedef struct ForTree { 

    Token varName;                           //x
    ExpressionTreeNode start;                //0
    ExpressionTreeNode end;                  //10
    ExpressionTreeNode increment;            //1
    IfTree ifTree;                           //Same as an if tree but with a jump

} ForTree;


typedef struct FunctionDeclarationTree { 

    Token functionName;                      //add

    Token returnType;                        //int*
    
    Token *dataType;                         //Array of datatypes (corrospond with variable names)
    Token *varName;                          //Input names

} FunctionDeclarationTree;




#endif // COMPILE_H 






