#include "tokenise.h"

HashMap validTokenHashmap; //Set this to global since only one should exist

//NOTE: This string does not work properly: for(int i=0,i<10,i++)

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
    case '|': 
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
    printf("Recieved: '%s'\n", line);
    for(size_t i = 0, j = 0; i < strlen(line); i++, j++) {
        completeToken = true;
        maybeVariable = false;
        
        if(line[i] == ' ') {
            j--; //Increment downwards to preserve array
            continue; //Should only happen if first character is whitespace

        } else if(isalpha(line[i]) != 0) {
            //is a character            
            containsChar = true;

        } else if(isdigit(line[i]) != 0) {
            //Is a digit
            containsNumbers = true;

        } else if(line[i] == '.') {
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

        if((containsChar == true && containsArithmaticSymbols == false && containsMiscSymbols == false)
        && (is_misc_symbol(line[i + 1]) == true) && line[i+1] != '|' && numberOfDecimals == 0) {

            printf("'%s' could be a variable\n",currentTokenLine);
            maybeVariable = true; //Use this flag to indicate that the current item might be a variable or char - see outcome of hashing
            //Do nothing, no assignment needed

        //Check for arithmatic symbols
        } else if((containsChar == false && containsNumbers == false) && (containsArithmaticSymbols == true)) {

            //Do nothing

            printf("'%s' is a arithmatic symbol\n",currentTokenLine);
        //Check for misc symbols
        //j == 0 checks if length == 0
        } else if(containsMiscSymbols == true && j == 0 && line[i+1] != '|') {

            printf("'%s' is a misc symbol\n",currentTokenLine);
            //If the length is 1 and it contains these tokens its already complete

        //Check for decimals and integers
        } else if(containsNumbers == true && containsChar == false && numberOfDecimals <= 1 && is_misc_symbol(line[i+1]) == true && line[i+1] != '|') {
            //Decide if its an int or float
            if(numberOfDecimals == 0) {
                //Set it as an integer (it can adjusted later in parser)

                printf("'%s' is a integer\n",currentTokenLine);
                currentToken.intImmediate = atoi(currentTokenLine);
            
            } else {
                
                printf("'%s' is a float\n",currentTokenLine);
                currentToken.floatImmediate = atof(currentTokenLine);
            }


        //Check for character immediate (e.g c' <- note ' at the end indicating its a char immediate not a var)
        } else if(j == 0 && line[i + 1] == '|') {

            
            printf("'%s' is a char\n",currentTokenLine);
            currentToken.charImmediate = currentTokenLine[i];

        } else {
            completeToken = false;
        }
        //printf("Contains char: %d, j = %zu, line[i+1] = %c, buffer: %s\n",containsChar, j, line[i+1], currentTokenLine);

        //If the token is not complete just continue
        if(completeToken == false) {
            continue;
        }

        //Add a '\0' to indicate end of string
     
        currentTokenLine[j + 1] = '\0';

        printf("Attempting to hash '%s'\n", currentTokenLine);






        //Check if token is valid - if so append it to the vector of tokens
        j = -1; //Get ready to load the next tokens into the array (set to -1 since j gets incremented)
        const void *hashmapValueOut = NULL;


        //Hash the token

        if(hashmap_get_value(&validTokenHashmap, currentTokenLine, &hashmapValueOut) == false) {
            
            goto temp; //TEMPORARY
            vector_destroy(tokensOut);
            
            //Unrecognised token - didnt even hash properly
            printf("Unrecognised token '%s'\n",currentTokenLine);
            return false;
        
        }


        //Check token validity
        if(hashmapValueOut != NULL) {
            //Valid token - append it to vector of tokens

            if(vector_quick_append(tokensOut, &currentToken, 1) == false) {
                vector_destroy(tokensOut);
                return false;
                
            }




        //Check for variable before printing syntax error
        } else {



            if(maybeVariable == true) {
                //It was a variable and not a keyword so not a syntax error

                if(vector_quick_append(tokensOut, currentTokenLine, strlen(currentTokenLine)) == false) {
                    vector_destroy(tokensOut);
                    return false;
                }


            } else {

                goto temp;
                vector_destroy(tokensOut);
                printf("Unrecognised token '%s'\n",currentTokenLine);
                return false; //Unrecognised token - syntax error
            }

        }

temp:
        containsChar = false;
        containsArithmaticSymbols = false;
        containsMiscSymbols = false;
        containsNumbers = false;
        numberOfDecimals = 0;
        maybeVariable = false;

    }

    printf("Leftover: %s\n",currentTokenLine);
    return true;
}


