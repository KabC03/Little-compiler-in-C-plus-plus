#include "parse.h"





/**
 * parse 
 * ===============================================
 * Brief: Parse an array of tokens - Generate IR 
 * 
 * Param: *tokens - Vector of input tokens 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool parse(Vector *tokens) {

    if(tokens == NULL) {
        return false;

    } else {

        //If first token is a brace then pop off jump label from conditional statement
        //Then if the next is a keyword then tokenise that as per normal
        if(vector_get_length(tokens) == 0) {
            printf("RECIEVED EMPTY TOKENS\n");
            return false;
        }


    }

    return true;
}




































