#include "parse.h"


size_t inputTokenLength = 0;                  //Global so every function can access this
size_t startingTokenIndex = 0;                //Current working index into the token array - updated by individual parsing function







//Parse comments - token stream as input and uses startingTokenIndex to index into vector
RETURN_CODE parse_comment(Vector *tokens) {

    if(tokens == NULL)  {
        return _NULL_PTR_PASS_;
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

    //Set the token length
    inputTokenLength = vector_get_length(tokens);

    //Start loop by setting the first token in the token vector
    //Is updated by each function in the switch case (what token should be processed and at what index)
    const Token *currentFirstToken = (Token*)vector_get_index(tokens, 0);
    if(currentFirstToken == NULL) {
        printf("Unexpected NULL token\n");
        return _GENERIC_FAILURE_; 
    }


    //Used to maintain state - e.g if in the middle of a function declaration - must finish the function declaration before token stream stops
    bool validEndOfTokenStream = false;
    while(1) {

        if(validEndOfTokenStream == true && currentFirstToken->floatImmediate == EOF) {
            break;
        }


        //currentFirsToken gets updated in individual parsing functions below
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
    }


    return _SUCCESS_;
}




















