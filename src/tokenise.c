//14, Jul, 24
#include "tokenise.h"
#define DECIMAL_POINT '.'
#define SINGLE_QUOTE '\''
#define CHAR_IMMEDIATE_SIZE 3
#define CHAR_IMMEDIATE_INDEX 1

typedef struct CurrentTokenMetadata {

    size_t numberOfDecimals;     //Number of decimal points encountered
    size_t numberOfSingleQuotes; //Number of single quotes encountered
    bool containsLoneTokens;     //Braces, commas, dots, etc
    bool containsSymbol;         //Symbol, but not a lone token
    bool containsNumbers;        //Contains 0-9
    bool containsLetters;        //Contains ASCII characters 

} CurrentTokenMetadata;
CurrentTokenMetadata currentTokenMetadata; //Global since many functions will need to access this
StringHashmap tokeniserValidTokenHashmap;
char *tempTokenBuffer; 



/**
 * print_tokens 
 * ===============================================
 * Brief: Prints an array of tokens 
 * 
 * Param: *tokensToPrint - Vector of tokens to print
 * 
 * Return: RETURN_CODE - Indicating succes or type of failure 
 * 
 */
RETURN_CODE print_tokens(Vector *tokensToPrint) {

    if(tokensToPrint == NULL) {
        return _INVALID_ARG_PASS_;

    } else {

        const char *userStringOut;
        size_t vectorSize = vector_get_length(tokensToPrint) + 1;
        Token *currentToken = NULL;
        for(size_t i = 0; i < vectorSize; i++) {

            currentToken = (Token*)vector_get_index(tokensToPrint, i);
            if(currentToken == NULL) {
                printf("CANNOT OBTAIN TOKEN\n");
                return _INTERNAL_ERROR_;
            }

            switch (currentToken->tokenEnum) {
            case EOF_TOKEN:
                printf("EOF\n");
                continue;
                break;
            case INT_IMMEDIATE:
                printf("int: '%d', ",currentToken->intImmediate);
                continue;
                break;
            case FLOAT_IMMEDIATE:
                printf("float: '%f', ",currentToken->floatImmediate);
                continue;
                break;
            case CHAR_IMMEDIATE:
                printf("char: '%c', ",currentToken->charImmediate);
                continue;
                break;
            case USER_STRING:

                userStringOut = dynamic_string_read(&(currentToken->userString));
                if(userStringOut == NULL) {
                    printf("CANNOT OBTAIN STRING TOKENAL ERROR\n");
                    return _INTERNAL_ERROR_;
                }
                printf("str: '%s', ",userStringOut);
                continue;
                break;
            default:
                break;
            }

            printf("enum: '%s', ", validTokens[currentToken->tokenEnum]);

        }

        return _SUCCESS_;
    }

    return _INTERNAL_ERROR_;
}





//Initialises tokeniser structures
RETURN_CODE internal_tokeniser_initialiser(Vector *tokensOut) {

    if(tokensOut == NULL) {
        return _INVALID_ARG_PASS_;
    }


    if(string_hashmap_initialise(&(tokeniserValidTokenHashmap), NUMBER_OF_TOKENS) == false) {
        return _INTERNAL_ERROR_;
    }

    for(VALID_TOKEN_ENUM i = 0; i < NUMBER_OF_TOKENS; i++) {


        if(string_hashmap_set(&(tokeniserValidTokenHashmap), (void*)(validTokens[i]), strlen(validTokens[i]) + 1, (void*)(&i), sizeof(VALID_TOKEN_ENUM)) == false) {
            return _INTERNAL_ERROR_;
        }

    }
    //string_hashmap_print(&tokeniserValidTokenHashmap);


    if(vector_initialise(tokensOut, sizeof(Token)) == false) {
        //TODO: Add string hashmap destroy function here 
        return _INTERNAL_ERROR_;
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
    currentTokenMetadata.numberOfSingleQuotes = 0;

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
    case '<':
    case '>':
    case ';':
    case ',':

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


    } else if(character == SINGLE_QUOTE) {
        //Contains a decimal point
        currentTokenMetadata.numberOfSingleQuotes++;

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


    if(internal_is_lone_token(nextChar) == true) {
        //If the next char is a lone token then the token is complete

        return true;

    } else if(currentTokenMetadata.containsLoneTokens == true) {
        //Lone symbols ALWAYS are their own token - doesnt matter whats next
    
        return true;

    } else if(currentTokenMetadata.containsSymbol == true && internal_is_symbol(nextChar) == false) {
        //Regular symbols need to be followed by a non-symbol to be complete
        return true;

    } else if((currentTokenMetadata.containsLetters == true || currentTokenMetadata.containsNumbers) \
    && (internal_is_symbol(nextChar) == true || internal_is_lone_token(nextChar) == true)) {
        //User strings (varable names, functions, etc) must be followed by a symbol to be complete
        //Same with immediates
        
        return true;

    } else {

        //Token is not complete
        return false;
    }
    


    return false;
}

//Set the immediate in the current token
RETURN_CODE internal_attempt_set_immediate_or_user_string(Token *tokenToAppendTo, char *tempTokenBuffer) {

    if(tokenToAppendTo == NULL || tempTokenBuffer == NULL) {
        return _INVALID_ARG_PASS_;
    } else {

        //Check for integer immediate
        //Only numbers allowed
        if(currentTokenMetadata.containsLetters == false && currentTokenMetadata.containsLoneTokens == false && currentTokenMetadata.containsSymbol == false &&
        currentTokenMetadata.numberOfDecimals == 0 && currentTokenMetadata.numberOfSingleQuotes == 0 && currentTokenMetadata.containsNumbers == true) {
            tokenToAppendTo->tokenEnum = INT_IMMEDIATE; 
            tokenToAppendTo->intImmediate = atoi(tempTokenBuffer);
            
            //printf("DETECTED INT IMMEDIATE: %s\n", tempTokenBuffer);

        } else if(currentTokenMetadata.containsLetters == false && currentTokenMetadata.containsLoneTokens == false && currentTokenMetadata.containsSymbol == false &&
        currentTokenMetadata.numberOfDecimals == 1 && currentTokenMetadata.numberOfSingleQuotes == 0 && currentTokenMetadata.containsNumbers == true) {
            //Check for float immediate
            //Only numbers AND a single '.'

            tokenToAppendTo->tokenEnum = FLOAT_IMMEDIATE; 
            tokenToAppendTo->floatImmediate = atof(tempTokenBuffer);
            //printf("DETECTED FLOAT IMMEDIATEL %s\n",tempTokenBuffer);

        } else if(currentTokenMetadata.containsLetters == true && currentTokenMetadata.containsLoneTokens == false && currentTokenMetadata.containsSymbol == false &&
        currentTokenMetadata.numberOfDecimals == 0 && currentTokenMetadata.numberOfSingleQuotes == 2 && currentTokenMetadata.containsNumbers == false && strlen(tempTokenBuffer) == CHAR_IMMEDIATE_SIZE &&
        tempTokenBuffer[CHAR_IMMEDIATE_INDEX] != SINGLE_QUOTE) { //Use short circuit && (left evaluated before right so technically safe)
            //Check for char immediate
            //Single character surrounded by ''' quotes, size of the immediate == 3 
            tokenToAppendTo->tokenEnum = CHAR_IMMEDIATE; 
            tokenToAppendTo->charImmediate = tempTokenBuffer[CHAR_IMMEDIATE_INDEX]; //Grab whats in between the quotes ('c')
            //printf("DETECTED CHAR IMMEDIATE: %c\n",tempTokenBuffer[1]);

        } else if(currentTokenMetadata.containsLetters == true && currentTokenMetadata.containsLoneTokens == false && currentTokenMetadata.containsSymbol == false &&
        currentTokenMetadata.numberOfDecimals == 0 && currentTokenMetadata.numberOfSingleQuotes == 0) {
            //Check for user string
            //Contains letters and possibly a number
            //printf("DETECTED INPUT STRING: %s\n", tempTokenBuffer);
            tokenToAppendTo->tokenEnum = USER_STRING; 
            if(dynamic_string_initialise(&(tokenToAppendTo->userString)) == false) {
                return _INTERNAL_ERROR_;
            }

            //Add the string to the token
            if(dynamic_string_set(&(tokenToAppendTo->userString), tempTokenBuffer) == false) {

                //TODO: Destroy dynamic string
                return _INTERNAL_ERROR_;
            }


        } else {

            //Unrecognised invalid token sequence
            return _VALUE_ERROR_;
        }
        
    }

    return _SUCCESS_;
}

/**
 * tokenise 
 * ===============================================
 * Brief: Tokenises an input stream 
 * 
 * Param: inputString - Input buffer line to be tokenised 
 *        *tokensOut - Uninitialised output vector for tokens (points to a pre-allocated token array)
 * 
 * Return: RETURN_CODE - Indicating succes or type of failure 
 * 
 */
RETURN_CODE tokenise(char *inputString, Vector *tokensOut) {


    /*
    //Used to accept the file ptr but now decided it should take each line directly
    


    if(srcFilename == NULL || tokensOut == NULL) {
        return _INVALID_ARG_PASS_;
    } else {

        RETURN_CODE returnCode = internal_tokeniser_initialiser(tokensOut);
        if(returnCode != _SUCCESS_) {
            return returnCode;
        }


        FILE *srcFilePtr = fopen(srcFilename, "r");
        if(srcFilePtr == NULL) {
            return _FILE_NOT_OPENED_;
        }
    */

    RETURN_CODE returnCode = internal_tokeniser_initialiser(tokensOut);
    if(returnCode != _SUCCESS_) {
        return returnCode;
    }
    if(inputString == NULL || tokensOut == NULL) {

        return _INVALID_ARG_PASS_;
        




    } else {

        Token currentToken;


        //char charFromSrcFile = fgetc(srcFilePtr); //have to do this here because this needs to be one char behind nextCharFromSrcFile
       
        char charFromSrcFile = inputString[0];

        if(charFromSrcFile == '\0') {
            currentToken.tokenEnum = EOF_TOKEN;
            if(vector_quick_append(tokensOut, &currentToken, 1) == false) {
                return _INTERNAL_ERROR_;
            }
            /*
            if(fclose(srcFilePtr) != 0) {
                return _FILE_NOT_CLOSED_;
            }
            */
            return _SUCCESS_;
        }
        

        tempTokenBuffer = calloc(strlen(inputString) + 2, sizeof(char));
        if(tempTokenBuffer == NULL) {
            return _INTERNAL_ERROR_;
        }


        char nextCharFromSrcFile = '\0';
        for(size_t i = 0, j = 1; strlen(inputString); i++, j++) {
            if(charFromSrcFile == '\0') {
                currentToken.tokenEnum = EOF_TOKEN;
                if(vector_quick_append(tokensOut, &currentToken, 1) == false) {
                    return _INTERNAL_ERROR_;
                }
                break;
            }

            //nextCharFromSrcFile = fgetc(srcFilePtr);
            nextCharFromSrcFile = inputString[j];
            //printf("letter: %c\n", nextCharFromSrcFile);



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

                /*
                if(fclose(srcFilePtr) != 0) {
                    return _FILE_NOT_CLOSED_;
                }
                */
                return _INVALID_ARG_PASS_;
            }

            //printf("%s, %zu\n",tempTokenBuffer, j);
            //Only if the token is complete should it be hashed
            if(internal_is_complete_token(nextCharFromSrcFile) == false) {
                charFromSrcFile = nextCharFromSrcFile;

                continue;
            }
            //if the token is complete - should add a NULL terminator to the end for propper string handling
            tempTokenBuffer[i + 1] = '\0';

            charFromSrcFile = nextCharFromSrcFile;
            i = -1; //Set to -1 so it increments to 0 next loop


            //Do hashing here
            //Hash, if not in map then check for immediate or user string

            const void *validTokenHashmapOutput = string_hashmap_get_value(&tokeniserValidTokenHashmap, tempTokenBuffer, strlen(tempTokenBuffer) + 1);

            if(validTokenHashmapOutput == NULL) {
                //Must be an immediate or user string
                if(internal_attempt_set_immediate_or_user_string(&currentToken, tempTokenBuffer) != _SUCCESS_) {

                    printf("Unrecognised token: '%s'\n",tempTokenBuffer);
                    return _INTERNAL_ERROR_;
                }

            } else {
                //Key was found in the map

                //printf("KEYWORD WAS FOUND: '%s'\n",tempTokenBuffer);
                currentToken.tokenEnum = *(VALID_TOKEN_ENUM*)(validTokenHashmapOutput);
            }


            if(vector_quick_append(tokensOut,&currentToken, 1) == false) {
                
                /*
                if(fclose(srcFilePtr) != 0) {
                    return _FILE_NOT_CLOSED_;
                }
                */

                return _INTERNAL_ERROR_;
            }


            //Reset the token metadata
            internal_reset_token_metadata();
        }


        /*
        if(fclose(srcFilePtr) != 0) {
            return _FILE_NOT_CLOSED_;
        }
        */
    }


    return _SUCCESS_;
}








