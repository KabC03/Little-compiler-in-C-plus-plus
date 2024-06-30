#include "tokenise.h"

HashMap validTokenHashmap; //Set this to global since only one should exist



//Checks if a character is a misc symbol
bool is_misc_symbol(char character) {

    switch (character) {
    case '(': 
    case ')': 
    case '[': 
    case ']': 
    case '{': 
    case '}': 
    case ',': 
    case ';': 
        return true;
    default:
        return false;
    }
    return true;
}



/**
 * initialise_valid_token_hashmap
 * ===============================================
 * Brief: Initialise the hashmap of valid tokens 
 * 
 * Param: 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool initialise_valid_token_hashmap(void) {

    if(hashmap_initialise(&validTokenHashmap, sizeof(char) * MAX_TOKEN_LENGTH, sizeof(TOKEN_TYPE), NUM_KEYWORDS) == false) {
        return false;
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

    //hashmap_print(&validTokenHashmap); //Idealy hash table shouldnt have any collisions

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

    if(line == NULL) {
        return false;
    }


    char currentToken[MAX_LINE_LENGTH] = "\0";
    
    if(vector_initialise(tokensOut, sizeof(Token)) == false) {
        return false;
    }


    bool containsChar = false;
    bool containsArithmaticSymbols = false;
    bool containsMiscSymbols = false;
    bool containsNumbers = false;
    size_t numberOfDecimals = 0;

    bool completeToken = false;
    for(size_t i = 0, j = 0; i < strlen(line); i++, j++) {

        if(isalpha(line[i]) == 0) {
            //is a character            
            containsChar = true;

        } else if(isdigit(line[i]) != 0) {
            //Is a digit
            containsNumbers = true;

        } else if(line[i] != '.') {
            //Contains a decimal point 
            numberOfDecimals++;

        } else {
            //Is a symbol
            if(is_misc_symbol(line[i]) == true) {
                containsMiscSymbols = true;
            } else {
                containsArithmaticSymbols = true;
            }
        }
        currentToken[j] = line[i];
        //Depending on next character  and if token contains symbols, numbers, letters (e.g ' ') decide if the token is complete so move onto the next


        //Tokens end when:        
        //Words should be followed by a symbol or whitespace
        //while(1)

        //Arithmatic operators should be followed by non-artithmatic operator (arithmatic operator is anything thats not a brace)
        //4 * (3+2) != 3

        //Misc symbols are ALWAYS considered as one token - basically anything that is not arithmatic
        //Braces, commas, semicolens


        //Variables contain letters and can contain numbers - NOTE cannot distinguish from function name at this stage - do in parser
        //Numbers must contain numbers and at max one decimal point
        //Char's must be of length one and adjacent to a symbol or whitespace 








        //Check if token is valid - if so append it to the vector of tokens
        if(completeToken == true) {
            const void *hashmapValueOut = NULL;

            if(hashmap_get_value(&validTokenHashmap, currentToken, &hashmapValueOut) == false) {
                vector_destroy(tokensOut);
                return false;
            }

            if(hashmapValueOut != NULL) {
                //Valid token - append it to vector of tokens

                if(vector_quick_append(tokensOut, currentToken, 1) == false) {
                    vector_destroy(tokensOut);
                    return false;
                }
            } else {
                vector_destroy(tokensOut);
                return false; //Unrecognised token - syntax error
            }
        } else {

            //Keep adding to the token array - token is not complete yet
            continue;
        }

    }


    return true;
}

