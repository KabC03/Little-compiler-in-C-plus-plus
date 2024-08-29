#include "parse.h"
#define VARIABLE_HASHMAP_SIZE 100
#define HERE printf("HERE\n");
#define FILE_NEWLINE(destFptr) if(fprintf(destFptr, "\n") < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_assert_token(tokenStream, index, assertedToken, assertedTokenAsStr, tokenOut)\
    tokenOut = (Token*)vector_get_index(tokenStream, index);\
    if(tokenOut == NULL) {\
        printf("%s - ", assertedTokenAsStr);\
        return _INVALID_ARG_PASS_;\
    } else if(tokenOut->tokenEnum != assertedToken) {\
        printf("%s - ", assertedTokenAsStr);\
        return _INVALID_ARG_PASS_;\
    }





StringHashmap variableStorage;  //Hashmap containing name -> VariableData
Vector registerStates;          //Registers storing data, index -> VariableData
size_t nextFreebaseOffset = 0;  //Next free memory offset available
FILE *globalIROut = NULL;



//Parse an expression
RETURN_CODE internal_parse_expression(Vector *tokens, size_t indexStart, size_t indexEnd ,VariableData *destRegMetadata) {


    if(tokens == NULL || destRegMetadata == NULL) {
        return _INVALID_ARG_PASS_;
    }
    //NOTE: Order matters
    //x = x*3 IS NOT THE SAME as x = 3*x
    //Second case sets x = 3 first then does 3*3 = 9, First case does x = x, then x = x*3

    //NOTE: Automatically saves registers before overwritting them
    //If not in registers, load from stack


    //Expect num, op, num, op, ...

    bool expectOperator = false;
    VALID_TOKEN_ENUM prevOp = INVALID_TOKEN;
    size_t rDest = -1;
    size_t rSrc = -1;


    for(size_t i = indexStart; i < indexEnd; i++) {

        Token *currentToken = (Token*)vector_get_index(tokens, i);
        if(currentToken == NULL) {
            return _INTERNAL_ERROR_;
        }
        if(expectOperator == true) {

            switch(prevOp) {
            case TOK_ADD: {
                
                internal_macro_addition(rDest, rSrc, globalIROut);
                break;
            } case TOK_SUB: {

                internal_macro_subtraction(rDest, rSrc, globalIROut);
                break;
            } case TOK_MUL: {

                internal_macro_multiplication(rDest, rSrc, globalIROut);
                break;
            } case TOK_DIV: {

                internal_macro_division(rDest, rSrc, globalIROut);
                break;

            } case INVALID_TOKEN: {

                rDest = rSrc;
                break;

            } default: {
                printf("Expected operator - ");
                return _INVALID_ARG_PASS_;
                break;
            }
            }
            prevOp = currentToken->tokenEnum;

        } else {

            switch(currentToken->tokenEnum) {
            case INT_IMMEDIATE: {

                //Load immediate into a register
                rSrc = register_load_to_register(&registerStates, &variableStorage, NULL, rDest, currentToken->intImmediate, globalIROut);
                internal_macro_load_immediate(rSrc, currentToken->intImmediate, globalIROut);
                break;
            } case USER_STRING: {

                //If variable in register set rSrc to its index
                

                //If variable not in register, load it into one
                const char *currentVarName = dynamic_string_read(&(currentToken->userString));
                if(currentVarName == NULL) {
                    return _INTERNAL_ERROR_;
                }
                VariableData *currentVar = (VariableData*)string_hashmap_get_value(&variableStorage, (void*)currentVarName, strlen(currentVarName) + 1);
                if(currentVar == NULL) {
                    return _INTERNAL_ERROR_;
                }

                if(currentVar->registerNumber != -1) { //In a register
                    rSrc = currentVar->registerNumber;
                 
                } else { //Must load into register
                    rSrc = register_load_to_register(&registerStates, &variableStorage, currentVar, rDest, currentToken->intImmediate, globalIROut) != _SUCCESS_;
                }

                break;

            } default: {
                printf("Expected operand - ");
                return _INVALID_ARG_PASS_;
                break;
            }
            }

        }

        expectOperator = !expectOperator;
    }
    return _SUCCESS_;
}







//Parse a 'set' statement
RETURN_CODE internal_parse_set(Vector *tokens) {

    FILE_NEWLINE(globalIROut);
    if(tokens == NULL) {
        return _INVALID_ARG_PASS_;
    }

    //set x = 10 + y + 2;
    Token *tokenOut;

    //Variable to write to
    internal_macro_assert_token(tokens, 1, USER_STRING, "Expected a variable name", tokenOut);
    //Check variable is declared
    const char *variableStr = dynamic_string_read(&(tokenOut->userString));

    //Get metadata
    VariableData *varWriteMetadata = (VariableData*)string_hashmap_get_value(&variableStorage, (void*)variableStr, strlen(variableStr) + 1);
    if(varWriteMetadata == NULL) {
        printf("Undeclared variable '%s' - ", variableStr);
        return _INTERNAL_ERROR_;
    }


    //Assert '='
    internal_macro_assert_token(tokens, 2, TOK_EQUALS_ASSIGNMENT, "Expected '='", tokenOut);



    //Calculate expression
    //Write the result to wherever the variable is stored
    RETURN_CODE returnVal = internal_parse_expression(tokens, 3, vector_get_length(tokens) - 1, varWriteMetadata);
    if(returnVal != _SUCCESS_) {
        return _INVALID_ARG_PASS_;
    }

    //Assert ';'
    internal_macro_assert_token(tokens, vector_get_length(tokens) - 1, TOK_SEMICOLEN, "Expected ';'", tokenOut);

    return _SUCCESS_;
}








//Parse declaration of a value
RETURN_CODE internal_parse_dec(Vector *tokens) {

    FILE_NEWLINE(globalIROut);
    if(tokens == NULL) {
        return _INVALID_ARG_PASS_;
    }
    //Make space on the stack, parse the expression

    //dec x = 10 + 2;

    Token *tokenOut;


    //Variable to write to
    internal_macro_assert_token(tokens, 1, USER_STRING, "Expected a variable name", tokenOut);
    //Check variable is declared
    const char *variableStr = dynamic_string_read(&(tokenOut->userString));

    //Get metadata
    VariableData *varWriteMetadata = (VariableData*)string_hashmap_get_value(&variableStorage, (void*)variableStr, strlen(variableStr));
    if(varWriteMetadata != NULL) {
        printf("Redeclaration of variable '%s' - ", variableStr);
        return _INTERNAL_ERROR_;
    }

    VariableData newVariableMetadata;
    newVariableMetadata.baseOffset = nextFreebaseOffset;
    nextFreebaseOffset += STACK_DATASIZE;
    newVariableMetadata.registerNumber = -1; //Specify new variable is not in a register
    newVariableMetadata.timesRequested = 0;
    newVariableMetadata.inUse = true;


    if(dynamic_string_initialise(&(newVariableMetadata.name)) == false) {
        return _INTERNAL_ERROR_;
    }
    if(dynamic_string_set(&(newVariableMetadata.name), variableStr) == false) {
        return _INTERNAL_ERROR_;
    }

    //Assert '='
    internal_macro_assert_token(tokens, 2, TOK_EQUALS_ASSIGNMENT, "Expected '='", tokenOut);

    //Calculate expression
    //Write the result to wherever the variable is stored
    RETURN_CODE returnVal = internal_parse_expression(tokens, 3, vector_get_length(tokens) - 1, &newVariableMetadata);
    if(returnVal != _SUCCESS_) {
        return _INVALID_ARG_PASS_;
    }


    //Add new variable to hashmap
    if(string_hashmap_set(&variableStorage, variableStr, strlen(variableStr) + 1, &newVariableMetadata, sizeof(VariableData)) == false) {
        return _INTERNAL_ERROR_;
    }

    //Assert ';'
    internal_macro_assert_token(tokens, vector_get_length(tokens) - 1, TOK_SEMICOLEN, "Expected ';'", tokenOut);


    register_print(&registerStates);
    return _SUCCESS_;
}



/**
 * parse_initialise 
 * ===============================================
 * Brief: Initialise the parser 
 * 
 * Param: void
 * 
 * Return: RETURN_CODE - Indicating succes or type of failure 
 * 
 */
RETURN_CODE parse_initialise(void) {

    if(string_hashmap_initialise(&variableStorage, VARIABLE_HASHMAP_SIZE) != true) {
        return _INTERNAL_ERROR_;
    }
    if(vector_initialise(&registerStates, sizeof(VariableData)) != true) {
        return _INTERNAL_ERROR_;
    }

    VariableData padding;
    padding.inUse = false;
    if(dynamic_string_initialise(&(padding.name)) == false) {
        return _INTERNAL_ERROR_;
    }
    if(dynamic_string_set(&(padding.name), "NULL") == false) {
        return _INTERNAL_ERROR_;
    }

    for(size_t i = 0; i < NUMBER_OF_REGISTERS; i++) { //Pad it with empty data
        if(vector_quick_append(&registerStates, &padding, 1) == false) {
            return _INTERNAL_ERROR_;
        }


    }

    return _SUCCESS_;
}






/**
 * parse 
 * ===============================================
 * Brief: Tokenise a line 
 * 
 * Param: *Tokens - Input vector of tokens  
 *        *irOut - Opened file pointer to output
 * 
 * Return: RETURN_CODE - Indicating succes or type of failure 
 * 
 */
RETURN_CODE parse(Vector *tokens, FILE *irOut) {

    if(tokens == NULL || irOut == NULL) {
        return _INVALID_ARG_PASS_; 
    
    } else {
    
        globalIROut = irOut;

        //First token determines what the line does
        VALID_TOKEN_ENUM *instructionToken = (VALID_TOKEN_ENUM*)vector_get_index(tokens, 0);
        
        if(instructionToken == NULL) {
            return _INTERNAL_ERROR_;
        }

        switch(*instructionToken) {

        //NOTE: For each instruction fill out  a 'struct' containing all data, then pass the struct to a macro which generates assembly

        case TOK_SET: //Variable change

            if(internal_parse_set(tokens) != _SUCCESS_) {
                return _INVALID_ARG_PASS_;
            }
            break;
        case TOK_VAR_DECL: //Variable declaration
            if(internal_parse_dec(tokens) != _SUCCESS_) {
                return _INVALID_ARG_PASS_;
            }
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













