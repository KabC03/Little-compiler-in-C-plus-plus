#include "parse.h"








/**
 * parse 
 * ===============================================
 * Brief: Tokenise a line 
 * 
 * Param: *Tokens - Input vector of tokens  
 * 
 * Return: RETURN_CODE - Indicating succes or type of failure 
 * 
 */
RETURN_CODE parse(Vector *Tokens) {

    if(Tokens == NULL) {
        return _INVALID_ARG_PASS_; 
    
    } else {
    
        //First token determines what the line does
        VALID_TOKEN_ENUM *instructionToken = (VALID_TOKEN_ENUM*)vector_get_index(Tokens, 0);
        
        if(instructionToken == NULL) {
            return _INTERNAL_ERROR_;
        }

        switch(*instructionToken) {

        //NOTE: For each instruction fill out  a 'struct' containing all data, then pass the struct to a macro which generates assembly

        case TOK_SET: //Variable change

            break;
        case TOK_VAR_DECL: //Variable declaration

            break;
        case TOK_FUN_CALL: //Function call

            break;
        case TOK_FUN_DECL: //Function declaration

            break;

        case TOK_END_FN: //End a function declaration

            break; 
        case TOK_IF: //If statement

            break;

        case TOK_ENDIF: //End if statement

            break;
        case TOK_GTO: //Goto statement

            break;
        case TOK_LBL: //Label declaration

            break;

        case EOF_TOKEN: //Blank line - skip
            return _SUCCESS_;
            break;

        default:
            printf("Unrecognised instruction\n");
            return _INVALID_ARG_PASS_;
            break;
        }
    }
            
    return _SUCCESS_; 
}













