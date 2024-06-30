#include "tokenise.h"

HashMap keywordHashmap; //Set this to global since only one should exist

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
bool initialise_keyword_hashmap(void) {

    for(size_t i = 0; i < ; i++) {
        
        printf("i = %d\n",i);
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
bool tokenise(char *line, Vector tokensOut) {

    if(line == NULL) {
        return false;
    }


    char currentLine[MAX_LINE_LENGTH] = '\0';
    
    //Add tokens to a buffer then hash
    //Depending on next character  and if token contains symbols, numbers, letters (e.g ' ') decide if the token is complete so move onto the next

    for(size_t i = 0, j = 0; i < strlen(line); i++, j++) {


    }



    return true;
}

