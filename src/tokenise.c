#include "tokenise.h"

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



HashMap validTokenHashmap; //Set this to global since only one should exist
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

        } else if(isalpha(currentChar) != 0) {
            //is a character            
            tokenTypeData.containsChar = true;

        } else if(isdigit(currentChar) != 0) {
            //Is a digit
            tokenTypeData.containsNumbers = true;

        } else if(currentChar == DECIMAL_CHAR) {
            //Contains a decimal point 
            
            tokenTypeData.numberOfDecimals++;

        } else if(currentChar == DECIMAL_CHAR) {
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
        currentTokenLine[*j] = currentChar;
    }

    return true;
}


bool is_complete_token(char nextChar) {


    if(tokenTypeData.containsChar == false && tokenTypeData.containsNumbers == false 
    && tokenTypeData.isOwnToken == false && tokenTypeData.containsArithmaticSymbols == true) {
        //Arithmatic symbol encountered, to split off next token needs to be non arithmatic
        if(is_arithmatic_symbol(nextChar) == false) {
            return true;
        }
    } else {
        //All other tokens are split by whitespace, or ANY type of symbol
        if(is_own_token_symbol(nextChar) == true || 
        is_arithmatic_symbol(nextChar) == true || nextChar == SPACE) {
            return true;
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

        //Test for user string (or keyword)
        if(tokenTypeData.containsChar == true && token_type_data_contains_no_delimeter_symbols == true) {

            currentToken->Token = USER_STRING; //Note - includes operators like +,-,>=,etc

        //Test for float immediate
        } else if(tokenTypeData.containsChar == false && token_type_data_contains_no_delimeter_symbols == true 
        && tokenTypeData.numberOfDecimals == 1 && tokenTypeData.containsNumbers == true) {


            currentToken->floatImmediate = atof(currentTokenLine);
            currentToken->Token = FLOAT_IMMEDIATE;

        //Test for integer immediate
        } else if(tokenTypeData.containsChar == false && token_type_data_contains_no_delimeter_symbols == true 
        && tokenTypeData.numberOfDecimals == 0 && tokenTypeData.containsNumbers == true) {

            currentToken->floatImmediate = atoi(currentTokenLine);
            currentToken->Token = INT_IMMEDIATE;

        //Test for char immediate
        } else if(tokenTypeData.containsChar == true && tokenTypeData.numberOfSingleQuotes == 2 && strlen(currentToken) == CHAR_IMMEDIATE_LINE_SIZE) {

            currentToken->floatImmediate = currentTokenLine[1]; 
            currentToken->Token = CHAR_IMMEDIATE;

        } else {

            tokenTypeData.completeToken = false;
            
            
            return false;
        }
    }



    return true;
}



bool second_pass_token_definition() {






    return true;
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

    if(hashmap_initialise(&validTokenHashmap, sizeof(char) * MAX_TOKEN_LENGTH, sizeof(TOKEN_TYPE), NUM_KEYWORDS) == false) {
        return false;



    //NOTE - VARIABLE SIZE IS TEMPORAY
    }
    
    for(size_t i = 0; i < NUM_KEYWORDS; i++) {
        
        //Add tokens to a buffer then hash
        
        //printf("Inserting key: %s\n",validTokens[i]);
        if(hashmap_insert(&validTokenHashmap, (void*)(validTokens[i]), &i) == false) {
            //Cannot loop over enum so enum and tokens must just align
            hashmap_destroy(&validTokenHashmap);
            return false;
        }
    }


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
    char currentTokenLine[MAX_LINE_LENGTH] = "\0";
    if(vector_initialise(tokensOut, sizeof(Token)) == false) {
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
        if(is_complete_token(line[i+1]) == false) {
            continue;
        }




        //First pass tokenisation
        if(first_pass_token_definition(currentTokenLine, &currentToken) == false) {
            //If first pass was not enough do a second pass (hashing)
            if(second_pass_token_definition() == false) {
                
                printf("Unrecognised token '%s'\n",currentTokenLine);
                vector_destroy(tokensOut);
                return false;
            }
        }

        //Add token to array of tokens
        if(vector_quick_append(tokensOut, &currentToken, 1) == false) {
            vector_destroy(tokensOut);
            return false;
        }


        //Reset the token data and get ready for another token
        reset_token_data();
    }
    return true;
}

