#include "tokenise.h"


#define NULL_CHARACTER '\0'
#define DECIMAL_CHAR '.'
#define SINGLE_QUOTE '\''
#define SPACE ' '
#define CHAR_IMMEDIATE_LINE_SIZE 3
#define token_type_data_contains_no_delimeter_symbols (tokenTypeData.containsArithmaticSymbols == false && tokenTypeData.isOwnToken == false)


typedef struct TokenTypeData {

    bool containsChar;
    bool containsArithmaticSymbols;
    bool containsNumbers;
    bool isOwnToken;
    size_t numberOfDecimals;
    size_t numberOfSingleQuotes; //For char immediate


    bool completeToken;
    TOKEN_TYPE tokenType;

} TokenTypeData;



StringHashmap validTokenHashmap; //Set this to global since only one should exist
TokenTypeData tokenTypeData; //Only one should exist for tokenisation


//Reset token data
void reset_token_data(void) {
    
    tokenTypeData.completeToken = true;
    tokenTypeData.containsArithmaticSymbols = false;
    tokenTypeData.containsChar = false;
    tokenTypeData.containsNumbers = false;
    tokenTypeData.isOwnToken = false;
    tokenTypeData.numberOfDecimals = 0;
    tokenTypeData.numberOfSingleQuotes = 0;    

    tokenTypeData.tokenType = INVALID;
    
    return;
}


//Determines is a character is arithmatic (+,-,*,/, etc)
bool is_arithmatic_symbol(char character) {

    switch (character) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
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


//Determines if a token is garunteed to be a single char in length (therefore ALWAYS consider the token complete)
bool is_own_token_symbol(char character) {

    switch (character) {
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
    case ',':
    case '@': //Pointer is treated as its own token (even @@)
    case ';':

        return true;
    default:
        return false;
    }
    
    return false;
}






//Takes in the current token line and the current char in the line and adjusts the token type data and j accordingly
bool set_token_parameters(char *currentTokenLine, char currentChar, size_t *j) {


    if(currentTokenLine == NULL || j == NULL) {
        return false;
    } else {
        
        if(currentChar == ' ') {
            (*j)--; //Increment downwards to preserve array
            return true;
        } else if(isalpha(currentChar) != 0) {
            //is a character            
            tokenTypeData.containsChar = true;

        } else if(isdigit(currentChar) != 0) {
            //Is a digit
            tokenTypeData.containsNumbers = true;

        } else if(currentChar == DECIMAL_CHAR) {
            //Contains a decimal point 
            
            tokenTypeData.numberOfDecimals++;

        } else if(currentChar == SINGLE_QUOTE) {
            //Contains single quote

            tokenTypeData.numberOfSingleQuotes++;  

        } else if(is_arithmatic_symbol(currentChar) == true) {

            tokenTypeData.containsArithmaticSymbols = true;


        } else if(is_own_token_symbol(currentChar) == true) {

            tokenTypeData.isOwnToken = true;

        } else {
            //Unknown symbol
            return false;
        }
        currentTokenLine[(*j)] = currentChar;
        
    }

    return true;
}


bool is_complete_token(size_t *j, char nextChar) {

    if(j == NULL) {
        return false;
    } else {

        if(tokenTypeData.containsChar == false && tokenTypeData.containsNumbers == false 
        && tokenTypeData.isOwnToken == false && tokenTypeData.containsArithmaticSymbols == true) {
            //Arithmatic symbol encountered, to split off next token needs to be non arithmatic
            if(is_arithmatic_symbol(nextChar) == false) {
                return true;
            }

        } else if(tokenTypeData.isOwnToken == true && *j == 0) {    
            //Single length tokens (e.g brackets, commas, etc)

            return true;


        } else if(nextChar == NULL_CHARACTER) {    
            //If its the NULL character then token must be complete
            return true;

        } else {
            //All other tokens are split by whitespace, or ANY type of symbol
            if(is_own_token_symbol(nextChar) == true || 
            is_arithmatic_symbol(nextChar) == true || nextChar == SPACE) {

                return true;
            }
        }

    }

    return false;
}







//First pass for tokens - can determine if its an immediate or not, second pass needed to distinguish variable from keyword
bool first_pass_token_definition(char *currentTokenLine, Token *currentToken) {


    if(currentTokenLine == NULL || currentToken == NULL) {
        return false;
    } else {

        tokenTypeData.completeToken = true;


        //Test for float immediate
        if(tokenTypeData.containsChar == false && token_type_data_contains_no_delimeter_symbols == true 
        && tokenTypeData.numberOfDecimals == 1 && tokenTypeData.containsNumbers == true) {


            printf("FLOAT_IMMEDIATE: %s\n", currentTokenLine);
            currentToken->floatImmediate = atof(currentTokenLine);
            currentToken->Token = FLOAT_IMMEDIATE;

        //Test for integer immediate
        } else if(tokenTypeData.containsChar == false && token_type_data_contains_no_delimeter_symbols == true 
        && tokenTypeData.numberOfDecimals == 0 && tokenTypeData.containsNumbers == true && tokenTypeData.numberOfSingleQuotes == 0) {

            printf("INT_IMMEDIATE: %s\n", currentTokenLine);
            currentToken->floatImmediate = atoi(currentTokenLine);
            currentToken->Token = INT_IMMEDIATE;

        //Test for char immediate
        } else if(tokenTypeData.containsChar == true && tokenTypeData.numberOfSingleQuotes == 2 && strlen(currentTokenLine) == CHAR_IMMEDIATE_LINE_SIZE) {


            printf("CHAR_IMMEDIATE: %s\n", currentTokenLine);
            currentToken->floatImmediate = currentTokenLine[1]; 
            currentToken->Token = CHAR_IMMEDIATE;


        } else {

            //Check that token is a valid string

            printf("FIRST PASS CANNOT DETERMINE TYPE: '%s'\n",currentTokenLine);
            currentToken->Token = USER_STRING; //Contains symbols, keywords, variables - figure out on second pass
        }
    }


    printf("\n");
    return true;
}


//Hash the token to get the reserved word
const void *second_pass_token_definition(char *currentTokenLine) {

    const void *data = NULL;
    if(currentTokenLine == NULL) {
        return NULL;
    } else {


        printf("SECOND PASS IS HASHING: '%s'\n",currentTokenLine);


        data = string_hashmap_get_value(&validTokenHashmap, currentTokenLine, strlen(currentTokenLine) + 1);
    }

    return data;
}


//Final variable check before appending (should contain no symbols)
bool final_keyword_check(void) {

    if(tokenTypeData.containsChar == true && token_type_data_contains_no_delimeter_symbols == true && tokenTypeData.isOwnToken == false) {
        return true;
    }

    return false;
}







/**
 * initialise_compiler_hashmaps 
 * ===============================================
 * Brief: Initialise the hashmap of valid tokens and variable names 
 * 
 * Param: 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool initialise_compiler_hashmaps (void) {

    if(string_hashmap_initialise(&validTokenHashmap, NUM_KEYWORDS) == false) {
        return false;
    }


    
    for(size_t i = 0; i < NUM_KEYWORDS; i++) {
        
        //Add tokens to a buffer then hash
        
        //printf("Inserting key: %s\n",validTokens[i]);

        if(string_hashmap_set(&validTokenHashmap, (void*)(validTokens[i]), strlen(validTokens[i]) + 1, &i, sizeof(TOKEN_TYPE)) == false) {

            //TODO: Destroy the hashmap
        }
    }
    string_hashmap_print(&validTokenHashmap);

    return true;
}



/**
 * tokenise 
 * ===============================================
 * Brief: Tokenise a line of characters 
 * 
 * Param: *line - Line to tokenise 
 *        tokensOut - Vector of output tokens
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool tokenise(char *line, Vector *const tokensOut) {


    //Preprocessing
    if(line == NULL) {
        return false;
    }
    if(strlen(line) == 1 && line[0] == '\n') {
        
        //Only contains newlines
        return true;
    }
    //Remove any \n
    if(line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }



    //Tokenisation intialisation
    char *currentTokenLine = calloc(strlen(line) + 1, sizeof(char));
    if(currentTokenLine == NULL) {
        return false;
    }


    Token currentToken;          //Only one exists
    TokenTypeData tokenTypeData; //Only one exists
    //Initialise token data
    reset_token_data();
    printf("Recieved: '%s'\n", line);
    //Main loop
    for(size_t i = 0, j = 0; i < strlen(line); i++, j++) {


        //Set token parameters
        if(set_token_parameters(currentTokenLine, line[i], &j) == false) {
            printf("Unexpected symbol '%c'\n",line[i]);
            return false;
        }

        
        //Decide if token is complete
        if(is_complete_token(&j, line[i+1]) == false) {
            continue;
        }

        //Token is complete so null terminate it
        currentTokenLine[j + 1] = '\0';
        if(strlen(currentTokenLine) == 0) { //Prevent whitespace getting through
            continue;
        }
        //First pass tokenisation
        if(first_pass_token_definition(currentTokenLine, &currentToken) == true) {
            //If first pass was not enough do a second pass (hashing)

            if(currentToken.Token != USER_STRING) {

            } else {
                //Second hash is only required if the token is still unknown


                const void *hashOutToken = second_pass_token_definition(currentTokenLine);
                if(hashOutToken == NULL) {
                    //Variable encountered
                    printf("TOKEN '%s' IS VARIABLE\n",currentTokenLine);
                    currentToken.Token = USER_VARIABLE_STRING;


                    //Make sure the variable is actually valid
                    if(final_keyword_check() == false) {
                        printf("Unrecognised token: '%s'\n",currentTokenLine);
                        return false;
                    }

                    currentToken.userString = malloc(strlen(currentTokenLine) + 1);
                    if(currentToken.userString == NULL) {
                        return false;
                    }


                    strcpy((currentToken.userString), currentTokenLine);

                } else {


                    //Set keyword to hashmap ouput
                    printf("FOUND TOKEN '%d'\n",*(TOKEN_TYPE*)hashOutToken);
                    currentToken.Token = *(TOKEN_TYPE*)(hashOutToken);
                }
            }

            j = -1;
        } else {
            //First pass tokenisation should ALWAYS pass for valid tokens

            printf("Unrecognised token: '%s'\n",currentTokenLine);
            return false;
        }

        //Add token to array of tokens
        if(vector_quick_append(tokensOut, &currentToken, 1) == false) {
            vector_destroy(tokensOut);
            return false;
        }


        //Reset the token data and get ready for another token
        reset_token_data();
    }
    printf("Returning true\n");
    return true;
}

