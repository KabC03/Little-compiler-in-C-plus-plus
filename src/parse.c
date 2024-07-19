//14, Jun, 2024
#include "parse.h"


#define LOCAL_HASHMAP_SIZE 100                //Local hashmap size for function and variable metadatas
#define SIZEOF_INTEGER 4
#define SIZEOF_FLOAT 4
#define SIZEOF_CHAR 4 //Should be 1 - to match UTF-8 but chose 4 so that its always memory aligned


//Assert a single token (like ; at the end of a statement) - Also increments counter automatically
#define internal_assert_token(TOKEN, SYMBOL) \
    //TOKEN - Token to assert e.g - OPEN_ANGLE_BRACE
    //SYMBOL - The symbol actually expected e.g - <
    do {\
        const Token *currentToken = vector_get_index(inputTokens, inputTokenIndex;\
        if(currentToken == NULL) {\
            return _FAILED_TO_CLOSE_FILE_
        

    } while(0);





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







































