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
        if(vector_get_length(tokens) == -1) {
            printf("RECIEVED EMPTY TOKENS\n");
            return false;
        } else {

            //Print recieved tokens:
            for(size_t i = 0; i < vector_get_length(tokens) + 1; i++) {
                printf("Current value: %d\n", *(int*)vector_get_index(tokens, i));
            }









        }
    }

    return true;
}




































