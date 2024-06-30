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
    case ' ':
    case '\0': 
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


    char currentTokenLine[MAX_LINE_LENGTH] = "\0";
    
    if(vector_initialise(tokensOut, sizeof(Token)) == false) {
        return false;
    }
    Token currentToken;

    bool containsChar = false;
    bool containsArithmaticSymbols = false;
    bool containsMiscSymbols = false;
    bool containsNumbers = false;
    size_t numberOfDecimals = 0;

    bool maybeVariable = false;

    bool completeToken = true;
    for(size_t i = 0, j = 0; i < strlen(line); i++, j++) {

        completeToken = true;
        maybeVariable = false;
        if(line[i] == ' ') {
            continue; //Should only happen if first character is whitespace

        } else if(isalpha(line[i]) == 0) {
    
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
        currentTokenLine[j] = line[i];
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


        //Check stuff here - then if token is complete set completeToken = true otherwise set it false and move on 

        

        //Check for keywords - note variables will also pass this filter - need to handle accordingly
        if((containsChar == true && containsArithmaticSymbols == false && containsNumbers == false && containsMiscSymbols == false)
        && (is_misc_symbol(line[i + 1]) == true)) {

            maybeVariable = true; //Use this flag to indicate that the current item might be a variable or char - see outcome of hashing
            //Do nothing, no assignment needed

        //Check for arithmatic symbols
        } else if((containsChar == false && containsNumbers == false) && (containsArithmaticSymbols == true)) {

            //Do nothing

        //Check for misc symbols
        //j == 0 checks if length == 0
        } else if(containsMiscSymbols == true && j == 0) {

            //If the length is 1 and it contains these tokens its already complete

        //Check for decimals and integers
        } else if(containsNumbers == true && containsChar == false && numberOfDecimals <= 1) {
            
            //Decide if its an int or float
            if(numberOfDecimals == 0) {
                //Set it as an integer (it can adjusted later in parser)
                currentToken.intImmediate = atoi(currentTokenLine);
            
            } else {
                currentToken.floatImmediate = atof(currentTokenLine);
            }


        //Check for character immediate (e.g c' <- note ' at the end indicating its a char immediate not a var)
        } else if(containsChar == true && j == 0 && currentTokenLine[i + 1] == '\'') {

            currentToken.charImmediate = currentTokenLine[i];

        } else {

            completeToken = false;
        }



        //Check if token is valid - if so append it to the vector of tokens
        if(completeToken == true) {
            j = 0; //Get ready to load the next tokens into the array
            const void *hashmapValueOut = NULL;


            if(hashmap_get_value(&validTokenHashmap, currentTokenLine, &hashmapValueOut) == false) {

                vector_destroy(tokensOut);
                return false;
            }





            if(hashmapValueOut != NULL) {
                //Valid token - append it to vector of tokens

                if(vector_quick_append(tokensOut, &currentToken, 1) == false) {
                    vector_destroy(tokensOut);
                    return false;
                }
            } else {



                if(maybeVariable == true) {
                    //It was a variable and not a keyword so not a syntax error
                    //NOTE: STORE IN HASHMAP FOR VARIABLES - DO THIS LATER

                } else {

                    vector_destroy(tokensOut);
                    printf("Unrecognised token '%s'\n",currentTokenLine);
                    return false; //Unrecognised token - syntax error
                }

            }
        } else {

            //Keep adding to the token array - token is not complete yet
            continue;
        }

    }


    return true;
}

