#include "parse.h"

#define internal_macro_assert_token(index, assert, assertString, tokenOutput)\
        VALID_TOKEN_ENUM* tokenOutput = (VALID_TOKEN_ENUM*)vector_get_index(Tokens, index);\
        if(tokenOutput != assert) {\
            printf("%s", assertString);\
            return _INVALID_ARG_PASS_;\
        }


typedef struct Expression {
    //Vector of tokens
    Vector tokens;

} Expression;

typedef struct TokenSetData {
    //set x = 10 + y + 2;
    StringHashmap variableAssigned;     
    Expression expression;     

} TokenSetData;



StringHashmap knownVariables; //Hashmap containing name -> stack offset


RETURN_CODE internal_parse_set(Vector *tokens) {

    if(tokens == NULL) {
        return _INVALID_ARG_PASS_;

    } else {

        Token currentToken;



        //Assert variable name
        internal_macro_assert_token(1, TOK_USER_STRING, "Expected variable name delimeter in set instruction", currentToken);
        char *variableName = dynamic_string_read(&(currentToken.userString));
        if(variableName == NULL) {
            return _INTERNAL_ERROR_; //Shouldnt happen
        }
        size_t variableStackOffset* = string_hashmap_get_value(&knownVariables, variableName, strlen(variableName) + 1); 


        //Assert '='
        internal_macro_assert_token(2, TOK_EQUALS_ASSIGNMENT, "Expected '=' delimeter in set instruction", currentToken);



        //Assert expression
        //TODO


        //Assign expression to variable
    }

    return _SUCCESS_;
}





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

            if(internal_parse_set(Vector *tokens) != _SUCCESS_) {
                return _INVALID_ARG_PASS_;
            }
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













