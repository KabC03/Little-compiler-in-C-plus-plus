//10, Jul, 24
#include "tokenise.h"



typedef struct CurrentTokenMetadata {

    bool containsLoneTokens; //Braces, commas, dots, etc
    bool symbol;             //Symbol, but not a lone token
    bool containsNumbers;    //Contains 0-9
    bool containsLetters;    //Contains ASCII characters

} CurrentTokenMetadata;
CurrentTokenMetadata currentTokenMetadata; //Global since many functions will need to access this
StringHashmap tokeniserValidTokenHashmap;
char tempTokenBuffer[MAX_TOKEN_LENGTH + 1]; 









//Initialises tokeniser structures
RETURN_CODE internal_tokeniser_initialiser(Vector *tokensOut) {

    if(tokensOut == NULL) {
        return _NULL_PTR_PASS_;
    }


    if(string_hashmap_initialise(&(tokeniserValidTokenHashmap), NUMBER_OF_TOKENS) == false) {
        return _GENERIC_FAILURE_;
    }

    for(VALID_TOKEN_ENUM i = 0; i < NUMBER_OF_TOKENS; i++) {


        if(string_hashmap_set(&(tokeniserValidTokenHashmap), (void*)(validTokens[i]), strlen(validTokens[i]) + 1, (void*)(&i), sizeof(VALID_TOKEN_ENUM)) == false) {
            return _GENERIC_FAILURE_;
        }

    }
    //string_hashmap_print(&tokeniserValidTokenHashmap);


    if(vector_initialise(tokensOut, sizeof(Token)) == false) {
        //TODO: Add string hashmap destroy function here 
        return _GENERIC_FAILURE_;
    }

    return _SUCCESS_;
}


bool internal_is_symbol(char character) {

    switch (character) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '@':
    case '=':
    case '>':
    case '<':
    case '!':

        return true;
         
    default:

        return false;
    }



    return false;
}



//Test if a lone token
bool internal_is_lone_token(char character) {

    switch (character) {
    case '{':
    case '}':
    case '[':
    case ']':
    case '(':
    case ')':
    case '.':
    case '\'':
    case ';':

        return true; 
        break;
    
    default:
        return false;
    }

    return false;
}



//Catagorise a character
bool internal_catagorise_character(char character) {

    if(isdigit(character) != 0) {
        //Digit encountered

    } else if(isascii(character) != 0) {
        //Letter encountered


    } else if(internal_is_lone_token(character) == true) {
    
    
    } else if(internal_is_symbol(character) == true) {
    
        //Letter encountered
    } else {
        
        //Unexpected character encountered
        return false;

    }



    
    return false;
}





/**
 * tokenise 
 * ===============================================
 * Brief: Tokenises an input stream 
 * 
 * Param: *srcFilename - Source file name to be tokenised
 *        *tokensOut - Uninitialised output vector for tokens (points to a pre-allocated token array)
 * 
 * Return: RETURN_CODE - Indicating succes or type of failure 
 * 
 */
RETURN_CODE tokenise(char *srcFilename, Vector *tokensOut) {

    if(srcFilename == NULL || tokensOut == NULL) {
        return _NULL_PTR_PASS_;
    } else {

        RETURN_CODE returnCode = internal_tokeniser_initialiser(tokensOut);
        if(returnCode != _SUCCESS_) {
            return returnCode;
        }


        FILE *srcFilePtr = fopen(srcFilename, "r");
        if(srcFilePtr == NULL) {
            return _FAILED_TO_OPEN_FILE_;
        }


        char charFromSrcFile = "\0";
        for(size_t i = 0, j = 0; ;i++, j++) {
            charFromSrcFile = fgetc(srcFilePtr);
            if(charFromSrcFile == EOF) {
                break;
            }

            if(isspace(charFromSrcFile) != 0) { //Skip whitespace
                continue;
            }


            //Update the metadata based on the type of character present
            if(internal_catagorise_character(charFromSrcFile) == false) {
                printf("Unrecognisd character: '%c'\n", charFromSrcFile);
                return _UNRECOGNISED_ARGUMENT_PASS_;
            }




        }



        if(fclose(srcFilePtr) != 0) {
            return _FAILED_TO_CLOSE_FILE_;
        }
    }



    return _SUCCESS_;
}








