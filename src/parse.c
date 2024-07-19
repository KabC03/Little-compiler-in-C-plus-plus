//14, Jun, 2024
#include "parse.h"
#define handle_unexpected_null_token() printf("Unexpected NULL token encountered\n"); return _GENERIC_FAILURE_; 
#define LOCAL_HASHMAP_SIZE 100                //Local hashmap size for function and variable metadatas
#define SIZEOF_INTEGER 4


//Macro to make assertions cleaner
#define expect_singular_token_and_increment_counter(tokenEnumCode, expectMessage) \
    do {\
        currentToken = (Token*)vector_get_index(tokens, *(startingIndex)); \
        if(currentToken == NULL) { \
        \
            printf("%s\n", expectMessage); \
        } else { \
        \
            if(currentToken->tokenEnum != tokenEnumCode) { \
                printf("%s\n", expectMessage); \
                return _GENERIC_FAILURE_; \
            } \
        \
        } \
    } while (0);
    




//Metadata
typedef struct VariableMetadata {

    size_t offsetFromBasePointer;             //Offset from stack base pointer
    size_t numberOfCallsToVariable;           //How many times this variable has been requested (used to decide who to push out of a register when one is neeeded)
    size_t variableLocationInRegister;        //Register number containing the variable - if not contained then set this to 0
    //Static type checking 
    size_t indirectionLevel;                  //Number of @
    VALID_TOKEN_ENUM baseType;                //Base datatype (e.g char, float, int, etc)

} VariableMetadata;
StringHashmap functionNameToMetadataMap;
bool validEndOfTokenStream = false;           //Used to denote if it is correct to exit the program now (e.g main is defined, not in the middle of a statement)
bool mainIsDefined = false;                   //Used to denote if main function has been defined or not
typedef struct FunctionMetadata {

    StringHashmap variableNameToMetadataMap;  //Variable name to its metadata for the current function
    size_t numberOfVariables;                 //Used to keep track of the top of the stack from base pointer
    Stack jumpMetadata;                       //Metadata for any jumps (labels)
    //Static type checking
    VariableMetadata returnTypeMetadata;      //Metadata for the return type

} FunctionMetadata;
typedef struct JumpMetadata {

    size_t labelID;                           //Label ID to write at the end of the if statement (preceded with a '.' to avoid collisions)

} JumpMetadata;



