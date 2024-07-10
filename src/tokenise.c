//10, Jul, 24
#include "tokenise.h"
#define DECIMAL_POINT '.'


typedef struct CurrentTokenMetadata {

    size_t numberOfDecimals; //Number of decimal points encountered
    bool containsLoneTokens; //Braces, commas, dots, etc
    bool containsSymbol;     //Symbol, but not a lone token
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


//Reset metadata after a successful pass
void internal_reset_token_metadata(void) {

    currentTokenMetadata.containsLetters = false;
    currentTokenMetadata.containsLoneTokens = false;
    currentTokenMetadata.containsNumbers = false;
    currentTokenMetadata.containsSymbol = false;
    currentTokenMetadata.numberOfDecimals = 0;

    return;
}


//Contains a symbol
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
        currentTokenMetadata.containsNumbers = true;

    } else if(isalpha(character) != 0) {
        //Letter encountered
        currentTokenMetadata.containsLetters = true;

    } else if(internal_is_lone_token(character) == true) {
        //Is a lone token
        currentTokenMetadata.containsLoneTokens = true;

    } else if(character == DECIMAL_POINT) {
        //Contains a decimal point
        currentTokenMetadata.numberOfDecimals++;

    } else if(internal_is_symbol(character) == true) {
        //Is a symbol
        currentTokenMetadata.containsSymbol = true;


    } else {     
        //Unexpected character encountered
        return false;

    }



    
    return true;
}


//Determines if a token can be considered complete or not based on metadata and the next char
bool internal_is_complete_token(char nextChar) {

    //EOL-type whitespace indicates the current token should end
    switch (nextChar) {
    case EOF:
    case ' ':
    case '\0':
    case '\n':

        return true; 
    default:
        break;
    }

    //If the character is a symbol then next token should not be a symbol or whitespace for the token to be complete
    //If the character is NOT a symbol then the next token should be a symbol or whitespace for the token to be complete
    //Whitespace for both cases is already filtered out in the above switch statement


    if(currentTokenMetadata.containsLoneTokens == true) {
        //Lone symbols ALWAYS are their own token - doesnt matter whats next
    
        return true;

    } else if(currentTokenMetadata.containsSymbol == true && internal_is_symbol(nextChar) == false) {
        //Regular symbols need to be followed by a non-symbol to be complete

        return true;


    } else if(internal_is_symbol(nextChar) == true || internal_is_lone_token(nextChar) == true) {
        //User strings (varable names, functions, etc) must be followed by a symbol to be complete
        
        return true;
    } else {

        //Token is not complete
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

        Token currentToken;
        char charFromSrcFile = fgetc(srcFilePtr); //have to do this here because this needs to be one char behind nextCharFromSrcFile
        if(charFromSrcFile == EOF) {
            if(fclose(srcFilePtr) != 0) {
                return _FAILED_TO_CLOSE_FILE_;
            }
            return _SUCCESS_;
        }
        
        char nextCharFromSrcFile = '0';
        for(size_t i = 0; i < MAX_TOKEN_LENGTH; i++) {

            if(charFromSrcFile == EOF) {
                break;
            }

            nextCharFromSrcFile = fgetc(srcFilePtr);


            if(isspace(charFromSrcFile) != 0) { //Skip whitespace
                charFromSrcFile = nextCharFromSrcFile;
                i--; //Preserve index by decrementing
                continue;
            }


            //Append the new character to the buffer
            tempTokenBuffer[i] = charFromSrcFile;


            //Update the metadata based on the type of character present
            if(internal_catagorise_character(charFromSrcFile) == false) {
                printf("Unexpected character: '%c' with ASCII '%d'\n", charFromSrcFile, (unsigned char)(charFromSrcFile));

                if(fclose(srcFilePtr) != 0) {
                    return _FAILED_TO_CLOSE_FILE_;
                }
                return _UNRECOGNISED_ARGUMENT_PASS_;
            }


            //Only if the token is complete should it be hashed
            if(internal_is_complete_token(nextCharFromSrcFile) == false) {
                charFromSrcFile = nextCharFromSrcFile;
                continue;
            }

            //if the token is complete - should add a NULL terminator to the end for propper string handling
            tempTokenBuffer[i + 1] = '\0';
            charFromSrcFile = nextCharFromSrcFile;
            i = -1; //Set to -1 so it increments to 0 next loop

            printf("Token: %s\n",tempTokenBuffer);
            //Note: Tokeniser breaks with "for(int i = 0; i <10;i++);"
            // int i = 0; i <10;i++) ;


            //DO HASHING HERE



            if(vector_quick_append(tokensOut,&currentToken, 1) == false) {

                if(fclose(srcFilePtr) != 0) {
                    return _FAILED_TO_CLOSE_FILE_;
                }
                return _GENERIC_FAILURE_;
            }


            //Reset the token metadata
            internal_reset_token_metadata();
        }



        if(fclose(srcFilePtr) != 0) {
            return _FAILED_TO_CLOSE_FILE_;
        }
    }



    return _SUCCESS_;
}








