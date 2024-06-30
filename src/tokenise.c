#include "tokenise.h"

HashMap validTokenHashmap; //Set this to global since only one should exist

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
bool initialise_valid_token_hashmap(void) {

    if(hashmap_initialise(&validTokenHashmap, sizeof(char) * MAX_TOKEN_LENGTH, sizeof(TOKEN_TYPE), NUM_KEYWORDS) == false) {
        return false;
    }
    
    for(size_t i = 0; i < NUM_KEYWORDS; i++) {
        
        //Add tokens to a buffer then hash
        
        //printf("Inserting key: %s\n",validTokens[i]);
        hashmap_insert(&validTokenHashmap, (void*)(validTokens[i]), &i); //Cannot loop over enum so enum and tokens must just align
    }

    hashmap_print(&validTokenHashmap);

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


    char currentLine[MAX_LINE_LENGTH] = "\0";
    

    for(size_t i = 0, j = 0; i < strlen(line); i++, j++) {


        currentLine[j] = line[i];

        //Depending on next character  and if token contains symbols, numbers, letters (e.g ' ') decide if the token is complete so move onto the next

    }


    return true;
}

