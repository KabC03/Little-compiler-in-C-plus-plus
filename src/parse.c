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
StringHashmap functionNameToMetadataMap;
bool validEndOfTokenStream = false;           //Used to denote if it is correct to exit the program now (e.g main is defined, not in the middle of a statement)
bool mainIsDefined = false;                   //Used to denote if main function has been defined or not
typedef struct FunctionMetadata {

    StringHashmap variableNameToMetadataMap;  //Variable name to its metadata for the current function
    size_t numberOfVariables;                 //Used to keep track of the top of the stack from base pointer
    Stack jumpMetadata;                       //Metadata for any jumps (labels)
    //Static type checking
    size_t indirectionLevel;                  //Number of @
    VALID_TOKEN_ENUM baseType;                //Base datatype (char, float, int)

} FunctionMetadata;
typedef struct VariableMetadata {

    size_t offsetFromBasePointer;             //Offset from stack base pointer
    size_t numberOfCallsToVariable;           //How many times this variable has been requested (used to decide who to push out of a register when one is neeeded)
    size_t variableLocationInRegister;        //Register number containing the variable - if not contained then set this to 0
    //Static type checking 
    size_t indirectionLevel;                  //Number of @
    VALID_TOKEN_ENUM baseType;                //Base datatype (e.g char, float, int, etc)

} VariableMetadata;
typedef struct JumpMetadata {

    size_t labelID;                           //Label ID to write at the end of the if statement (preceded with a '.' to avoid collisions)

} JumpMetadata;




//Parse variable declarations - DOES NOT RESERVE STACK SPACE - MUST BE DONE IN OTHER FUNCTION - functionMetadata is the function of interest
RETURN_CODE parse_variable_declaration(Vector *tokens, size_t *startingIndex, FunctionMetadata *functionMetadata) {

    //<int, 2@> x (double pointer to an int)

    /*
    1. Check for <  
    2. Assign base type (int, float, char)
    3. If a > is encountered skip the next few steps
    4. Check for a comma
    5. If a @ is encountered indirection is 1
    6. If a number is encountered then indirection is equal to that
    7. Push onto the stack, and set the variables location to that spot
    NOTE: One variable per space since it avoids need to do manual alignment (also a performance benifit)
    */ 

    if(tokens == NULL || startingIndex == NULL || functionMetadata == NULL) {
        return _NULL_PTR_PASS_;
    } 

    //Get the <
    Token *currentToken = (Token*)vector_get_index(tokens, (*startingIndex)++);
    expect_singular_token_and_increment_counter(TOK_OPEN_ANGLE, "Expected a '<' in variable declaration");


    
    VariableMetadata variableMetadata;
    variableMetadata.numberOfCallsToVariable = 0;
    variableMetadata.variableLocationInRegister = 0; //Indicates NOT IN REGISTER
    //Get the base type
    currentToken = (Token*)vector_get_index(tokens, (*startingIndex)++);
    if(currentToken == NULL) {
        printf("Expected a base type in variable declaration\n");
        return _GENERIC_FAILURE_;
    }
    switch (currentToken->tokenEnum) {
    case TOK_INT:

        variableMetadata.baseType = TOK_INT;
        break;

    case TOK_FLT:
        
        variableMetadata.baseType = TOK_FLT;
        break;
    
    case TOK_CHR:
        
        variableMetadata.baseType = TOK_CHR;
        break;
    
    default:
        printf("Unrecognised datatype in declaration");
        return _GENERIC_FAILURE_;
    }


    //Search for another '>'
    currentToken = (Token*)vector_get_index(tokens, (*startingIndex)++);
    if(currentToken == NULL) {
        printf("Expected a '>' in variable declaration\n");
        return _GENERIC_FAILURE_;
    }
    if(currentToken->tokenEnum == TOK_CLOSE_ANGLE) {
        //End of type specifications - expect naming next
        //Do nothing here - just skip over the else

    } else {
        //Expect a comma then a pointer declaration and finally a >
        expect_singular_token_and_increment_counter(TOK_COMMA, "Expected a comma in declaration");



        //Expect a positive integer immediate 
        currentToken = (Token*)vector_get_index(tokens, (*startingIndex)++);
        if(currentToken == NULL) {
            printf("Expected an integer indirection counter in declaration statement\n");
            return _GENERIC_FAILURE_;
        } 
        if(currentToken->tokenEnum != INT_IMMEDIATE) {
            printf("Expected an integer indirection counter in declaration statement\n");
            return _GENERIC_FAILURE_;
        }
        if(currentToken->intImmediate <= 0) {
            printf("Integer indirection must be larger than zero in declaration statement\n");
            return _GENERIC_FAILURE_;

        }
        variableMetadata.indirectionLevel = currentToken->intImmediate;
        //Expect a @ 
        expect_singular_token_and_increment_counter(TOK_PTR, "Expected a '@' pointer operator");
        //Expect a >
        expect_singular_token_and_increment_counter(TOK_CLOSE_ANGLE, "Expected a '>' in variable declaration");
    }



    currentToken = (Token*)vector_get_index(tokens, (*startingIndex)++);
    if(currentToken == NULL) {
        printf("Expected variable name\n");
        return _GENERIC_FAILURE_;
    }
    const char *variableName = dynamic_string_read(&(currentToken->userString));
    if(variableName == NULL) {
        printf("Variable name unexpectedly NULL during assignment\n");
        return _GENERIC_FAILURE_;
    }

    variableMetadata.offsetFromBasePointer = ((functionMetadata->numberOfVariables)++) * SIZEOF_INTEGER;


    //Add variable name to hashmap, also add its offset from the base pointer
    //Assuming variable hashmap is already initialised
    if(string_hashmap_set(&(functionMetadata->variableNameToMetadataMap), (void*)variableName, strlen(variableName) + 1, &(variableMetadata), sizeof(VariableMetadata)) == false) {
        printf("Unable to append variable '%s' to hashmap\n", variableName);
        return _GENERIC_FAILURE_;
    }


    return _SUCCESS_;
}



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


    Token *currentToken = (Token*)vector_get_index(tokens, (*startingIndex)++);
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
    currentToken = (Token*)vector_get_index(tokens, (*startingIndex)++);
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



    FunctionMetadata functionMetadata;
    //Initialise the various structures inside the metadata


    if(stack_initialise(&(functionMetadata.jumpMetadata), sizeof(JumpMetadata)) == false) {
        printf("Unable to initialise stack during function declaration\n");
        return _GENERIC_FAILURE_;
    }
    if(string_hashmap_initialise(&(functionMetadata.variableNameToMetadataMap), LOCAL_HASHMAP_SIZE) == false) {
        printf("Unable to initialise hashmap during function declaration\n");
        return _GENERIC_FAILURE_;
    }


    while(1) {


        if(parse_variable_declaration(tokens, startingIndex, &functionMetadata) != _SUCCESS_) {
            return _GENERIC_FAILURE_;
        }
        

        //Expect a ',' to seperate the tokens
        currentToken = (Token*)vector_get_index(tokens, (*startingIndex)++);
        if(currentToken == NULL) {
            printf("Expected a ',' in function argument declaration\n");
            return _GENERIC_FAILURE_;
        }
    }



    //Expect a ')' token
    expect_singular_token_and_increment_counter(TOK_CLOSE_PAREN, "Expected a ')' in function declaration");




    //Add the return type
    if(parse_variable_declaration(tokens, startingIndex, &functionMetadata) != _SUCCESS_) {
        return _GENERIC_FAILURE_;
    }



    //Expect a { 
    expect_singular_token_and_increment_counter(TOK_OPEN_CURLEY, "Expected a '{' in function declaration");





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
        currentFirstToken = (Token*)vector_get_index(tokens, startingTokenIndex++);
        if(currentFirstToken == NULL) {
            handle_unexpected_null_token();
        }
    }


    return _SUCCESS_;
}




