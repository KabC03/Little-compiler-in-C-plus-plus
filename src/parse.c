#include "parse.h"
#define handle_unexpected_null_token() printf("Unexpected NULL token encountered\n"); return _GENERIC_FAILURE_; 
#define LOCAL_HASHMAP_SIZE 100                //Local hashmap size for function and variable metadatas


size_t inputTokenLength = 0;                  //Global so every function can access this
size_t startingTokenIndex = 0;                //Current working index into the token array - updated by individual parsing function
FILE *irOutputFile = NULL;                    //File stream - global so everything can write to it
//Metadata
StringHashmap functionNameToMetadataMap;
bool validEndOfTokenStream = false;           //Used to denote if it is correct to exit the program now (e.g main is defined, not in the middle of a statement)
bool mainIsDefined = false;                   //Used to denote if main function has been defined or not
typedef struct FunctionMetadata {

    StringHashmap variableNameToMetadataMap;  //Variable name to its metadata for the current function
    Stack jumpMetadata;                       //Metadata for any jumps (labels)

} FunctionMetadata;
typedef struct VariableNameMetadata {

    size_t offsetFromBasePointer;             //Offset from stack base pointer
    size_t numberOfCallsToVariable;           //How many times this variable has been requested (used to decide who to push out of a register when one is neeeded)
    size_t variableLocationInRegister;        //Register number containing the variable - if not contained then set this to 0

} VariableNameMetadata;
typedef struct JumpMetadata {

    labelID;                                  //Label ID to write at the end of the if statement (preceded with a '.' to avoid collisions)

} JumpMetadata;









//Parse expressions (binary expressions)
RETURN_CODE parse_expression(Vector *tokens) {

    return _SUCCESS_;
}



//Parse comments - token stream as input and uses startingTokenIndex to index into vector
RETURN_CODE parse_comment(Vector *tokens) {
    //This function is REALLY inefficient - work on it in the future


    if(tokens == NULL) {
        return _NULL_PTR_PASS_;
    }






    return _SUCCESS_;
}




//Parse function declaration
RETURN_CODE parse_function_declarations(Vector *tokens) {

    return _SUCCESS_;
}
//Parse variable delcarations
RETURN_CODE parse_variable_declarations(Vector *tokens) {

    return _SUCCESS_;
}
//Label declaration
RETURN_CODE parse_label_declaration(Vector *tokens) {

    return _SUCCESS_;
}




//Parse variable assignments
RETURN_CODE parse_variable_assignment(Vector *tokens) {

    return _SUCCESS_;
}
//Parse if statements 
RETURN_CODE parse_if_statement(Vector *tokens) {

    return _SUCCESS_;
}
//Goto statement
RETURN_CODE parse_goto_statement(Vector *tokens) {

    return _SUCCESS_;
}
//End of function or if statement (}):w
RETURN_CODE parse_end_of_statement(Vector *tokens) {

    return _SUCCESS_;
}





RETURN_CODE parse(Vector *tokens, char *irOutputFileName) {

    if(tokens == NULL || irOutputFileName == NULL) {
        return _NULL_PTR_PASS_;
    }

   
    //print_tokens(tokens);
    //irOutputFile = fopen(irOutputFileName, "w");
    //if(irOutputFile == NULL) {
    //    return _NULL_PTR_PASS_;
    //}


    if(string_hashmap_initialise(&functionNameToMetadataMap, LOCAL_HASHMAP_SIZE) == false) {
        return _INITIALISATION_FAILURE;
    }



    //Set the token length
    inputTokenLength = vector_get_length(tokens);

    //Start loop by setting the first token in the token vector
    //Is updated by each function in the switch case (what token should be processed and at what index)
    const Token *currentFirstToken = (Token*)vector_get_index(tokens, 0);
    if(currentFirstToken == NULL) {
        printf("Expected main function declaration\n");
        return _GENERIC_FAILURE_;
    }


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
        case TOK_COMMENT:
            if(parse_comment(tokens)  != _SUCCESS_) {
                return _GENERIC_FAILURE_;
            }
            break;

        default:
            printf("Unrecognised token: '%s'\n", validTokens[currentFirstToken->tokenEnum]);
            return _GENERIC_FAILURE_; 
            break;
        }



        //Set up for next token iteration
        currentFirstToken = vector_get_index(tokens, startingTokenIndex);
        if(currentFirstToken == NULL) {
            handle_unexpected_null_token();
        }
    }


    return _SUCCESS_;
}




