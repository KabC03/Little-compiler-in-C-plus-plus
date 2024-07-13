#include "parse.h"
#define handle_unexpected_null_token() printf("Unexpected NULL token encountered\n"); return _GENERIC_FAILURE_; 
#define LOCAL_HASHMAP_SIZE 100                //Local hashmap size for function and variable metadatas



//Macro to make assertions cleaner
#define expect_singular_token_and_increment_counter(tokenEnumCode, expectMessage) \
    do {\
        currentToken = (Token*)vector_get_index(tokens, *(startingIndex++)); \
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
StringHashmap functionNameToMetadataMap;
bool validEndOfTokenStream = false;           //Used to denote if it is correct to exit the program now (e.g main is defined, not in the middle of a statement)
bool mainIsDefined = false;                   //Used to denote if main function has been defined or not
typedef struct FunctionMetadata {

    StringHashmap variableNameToMetadataMap;  //Variable name to its metadata for the current function
    Stack jumpMetadata;                       //Metadata for any jumps (labels)
    //Static type checking
    size_t indirectionLevel;                  //Number of @
    Token baseType;                           //Base datatype (char, float, int)

} FunctionMetadata;
typedef struct VariableNameMetadata {

    size_t offsetFromBasePointer;             //Offset from stack base pointer
    size_t numberOfCallsToVariable;           //How many times this variable has been requested (used to decide who to push out of a register when one is neeeded)
    size_t variableLocationInRegister;        //Register number containing the variable - if not contained then set this to 0
    //Static type checking 
    size_t indirectionLevel;                  //Number of @
    Token baseType;                           //Base datatype (e.g char, float, int, etc)

} VariableNameMetadata;
typedef struct JumpMetadata {

    size_t labelID;                           //Label ID to write at the end of the if statement (preceded with a '.' to avoid collisions)

} JumpMetadata;




//Parse function declarations - modifies starting index but reads from irOutputFile
RETURN_CODE parse_function_declarations(Vector *tokens, size_t *startingIndex, const FILE *irOutputFile) {

    //fn main(<int, @, @> x, <float, @, @> y) <int, @, @> {
    //fn is already garunteed to be here - so ignore it

 
    /*
    1. Make sure function does not already exist - hashing it should return NULL 
    2. Hash the function name, and initialise its metadata
    3. Set the base pointer to point to the base of the stack
    4. Store the arguments at the base of the stack (sit above the return address) and record offsets in metadata
    */



    if(tokens == NULL || startingIndex == NULL || irOutputFile == NULL) {
        return _NULL_PTR_PASS_;
    }


    Token *currentToken = (Token*)vector_get_index(tokens, *startingIndex);
    const char *functionName = NULL;
    if(currentToken == NULL) {
        printf("Expected a function name\n");
        return _GENERIC_FAILURE_;
    } else {

        //Get the function name
        if(currentToken->tokenEnum != USER_STRING) {
            printf("Function name must be a string\n");
            return _GENERIC_FAILURE_;
        } else {

            functionName = (char*)dynamic_string_read(&currentToken->userString);
            if(functionName == NULL) {
                printf("Failed to read function name\n");
                return _GENERIC_FAILURE_;
            }

            //Make sure the function hasng been defined previously
            if(string_hashmap_get_value(&functionNameToMetadataMap, (void*)functionName, strlen(functionName) + 1) != NULL) {
                printf("Function '%s' is already defined\n",functionName);
                return _GENERIC_FAILURE_;
            }
        }
    }



    //Next token must be an open paren
    currentToken = (Token*)vector_get_index(tokens, *(startingIndex++));
    if(currentToken == NULL) {

        printf("Expected an open parenthesis in function declaration\n");
    } else {

        if(currentToken->tokenEnum != TOK_OPEN_PAREN) {
            printf("Expected open parenthesis in function declaration\n");
            return _GENERIC_FAILURE_;
        }

    }

    //Expect a '('
    expect_singular_token_and_increment_counter(TOK_OPEN_PAREN, "Expected a '(' in function declaration");
    


    //Now must expect variable declarations here - can be infinite amount of them
    //Parse variable declaration function should be called here
    //That function should handle the metadata stack stuff
    while(1) {

        //if(parse_variable_declaration() != _GENERIC_SUCCESS_ {}

        

        //Expect a ',' to seperate the tokens
        currentToken = (Token*)vector_get_index(tokens, *(startingIndex++));
        if(currentToken == NULL) {
            printf("Expected a ',' in function argument declaration\n");
            return _GENERIC_FAILURE_;
        }
    }



    //Expect a ')' token
    expect_singular_token_and_increment_counter(TOK_CLOSE_PAREN, "Expected a ')' in function declaration");




    //Add the return type
    //if(parse_variable_declaration() != _GENERIC_SUCCESS_ {}




    //Expect a { 
    expect_singular_token_and_increment_counter(TOK_OPEN_CURLEY, "Expected a '{' in function declaration");



    FunctionMetadata functionMetadata;


    //Append the metadata for the function
    if(string_hashmap_set(&functionNameToMetadataMap, (void*)functionName, strlen(functionName) + 1, &functionMetadata, sizeof(functionMetadata)) == false) {
        printf("Failed to append function metadata\n");
        return _GENERIC_FAILURE_;
    }

    return _SUCCESS_;
}










RETURN_CODE parse(Vector *tokens, char *irOutputFileName) {

    if(tokens == NULL || irOutputFileName == NULL) {
        return _NULL_PTR_PASS_;
    }

   
    //print_tokens(tokens);
    FILE *irOutputFile = fopen(irOutputFileName, "w");
    if(irOutputFile == NULL) {
        return _NULL_PTR_PASS_;
    }


    if(string_hashmap_initialise(&functionNameToMetadataMap, LOCAL_HASHMAP_SIZE) == false) {
        return _INITIALISATION_FAILURE;
    }




    //Start loop by setting the first token in the token vector
    //Is updated by each function in the switch case (what token should be processed and at what index)
    const Token *currentFirstToken = (Token*)vector_get_index(tokens, 0);
    if(currentFirstToken == NULL) {
        printf("Expected main function declaration\n");
        return _GENERIC_FAILURE_;
    }
    
    
    
    size_t startingTokenIndex = 0;

    while(1) {


        //Exit main loop
        if(validEndOfTokenStream == true && currentFirstToken->tokenEnum == EOF && mainIsDefined == true) {
            //Valid exit encountered, all required conditions are met
            break;
        } else if(currentFirstToken->tokenEnum == EOF) {
            printf("Incomplete statement\n");
            return _GENERIC_FAILURE_;
        }




        startingTokenIndex++; //Increment past the current token
    
        //Parsing functions
        switch (currentFirstToken->tokenEnum) {
        
        
        case TOK_FN:
            if(parse_function_declarations(tokens, &startingTokenIndex, irOutputFile)  != _SUCCESS_) {
                return _GENERIC_FAILURE_;
            }
            break;


        default:
            printf("Unrecognised token: '%s'\n", validTokens[currentFirstToken->tokenEnum]);
            return _GENERIC_FAILURE_; 
            break;
        }



        //Set up for next token iteration
        currentFirstToken = (Token*)vector_get_index(tokens, startingTokenIndex);
        if(currentFirstToken == NULL) {
            handle_unexpected_null_token();
        }
    }


    return _SUCCESS_;
}




