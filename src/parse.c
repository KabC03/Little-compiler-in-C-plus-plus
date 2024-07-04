#include "parse.h"


Stack conditionalJumpStack; //Holds size_t (ID for jump label)

typedef enum insideCurrentStructure {

    IN_UNDECLARED_SECTION, //No mode - expect a mode to be given
    IN_DATA_SECTION, 
    IN_FUNCTION_SECTION, 
    IN_PROGRAM_SECTION, 

} insideCurrentStructure;

/**
 * initialise_parser_structures 
 * ===============================================
 * Brief: Initialise parser structures before use 
 * 
 * Param: void 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool initialise_parser_structures(void) {

    if(stack_initialise(&conditionalJumpStack, sizeof(size_t)) == false) {
        return false;
    }



    return true;
}




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




































