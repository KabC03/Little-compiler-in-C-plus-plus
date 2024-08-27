#include "parse.h"
#define VARIABLE_HASHMAP_SIZE 100
#define HERE printf("HERE\n");

#define internal_macro_assert_token(tokenStream, index, assertedToken, assertedTokenAsStr, tokenOut)\
    tokenOut = (Token*)vector_get_index(tokenStream, index);\
    if(tokenOut == NULL) {\
        printf("%s - ", assertedTokenAsStr);\
        return _INVALID_ARG_PASS_;\
    } else if(tokenOut->tokenEnum != assertedToken) {\
        printf("%s - ", assertedTokenAsStr);\
        return _INVALID_ARG_PASS_;\
    }

typedef struct RegisterData { //Could definitely optimise the 'inUse' member but make it more readable for now
    //Held within the variableStorage string hashmap
    size_t baseOffset;     //Where the variable is stored on the stack
    size_t registerNumber; //Which register the variable is stoed in (-1 if not stored in register)
    size_t timesRequested; //Times this variable has been used (higher usage means it will stay in registers longer)
    bool inUse;            //If this register space is in use (to specify empty space in register state vector)

} RegisterData;



StringHashmap variableStorage;  //Hashmap containing name -> RegisterData
Vector registerStates;          //Registers storing data, index -> RegisterData
size_t nextFreebaseOffset = 0; //Next free stack offset available
FILE *globalIROut = NULL;



//Push a variable into a register for storage, blacklist a register
RETURN_CODE internal_push_into_registers(RegisterData *variable, size_t blacklistedRegisterIndex) {

    if(variable == NULL) {
        return _INVALID_ARG_PASS_;
    }

    size_t minUsedRegisterIndex = 0;
    for(size_t i = 0; i < vector_get_length(&registerStates) + 1; i++) {
        RegisterData *currentRegister = (RegisterData*)vector_get_index(&registerStates, i);
        if(currentRegister == NULL) {
            return _INTERNAL_ERROR_;
        }

        if(i == blacklistedRegisterIndex) {
            continue;;
        } else if(currentRegister->inUse == false) { //If register isnt being used then allow it to be used
            variable->registerNumber = i;
            break;

        } else if(currentRegister->timesRequested < minUsedRegisterIndex) {
            variable->registerNumber = i;
        }
    }

    //Save the register being pushed out
    internal_macro_save(minUsedRegisterIndex, ((RegisterData*)vector_get_index(&registerStates, minUsedRegisterIndex))->baseOffset, globalIROut);


    variable->timesRequested++; //Increment the times requested
    //Push mark the new variable as being stored in the register
    if(vector_set_index(&registerStates, variable->registerNumber, variable) == false) {
        return _INTERNAL_ERROR_;
    }

    return _SUCCESS_;
}


//Request a register to hold an immediate (marks it as unused so it can be overwritten), blacklist a register
RETURN_CODE internal_request_immediate_register(size_t *indexOut, size_t blacklistedRegisterIndex) {

    if(indexOut == NULL) {
        return _INVALID_ARG_PASS_;
    }

    RegisterData *currentRegister = NULL;

    size_t minUsedRegisterIndex = 0;
    for(size_t i = 0; i < vector_get_length(&registerStates) + 1; i++) {
        currentRegister = (RegisterData*)vector_get_index(&registerStates, i);
        if(currentRegister == NULL) {
            return _INTERNAL_ERROR_;
        }

        if(i == blacklistedRegisterIndex) {
            continue;;
        } else if(currentRegister->inUse == false) { //If register isnt being used then allow it to be used
            *indexOut = i;
            return _SUCCESS_;

        } else if(currentRegister->timesRequested < minUsedRegisterIndex) {
            *indexOut = i;
        }
    }

    currentRegister->inUse = false; //Set the new register as unused

    //Save the register being pushed out
    internal_macro_save(minUsedRegisterIndex, ((RegisterData*)vector_get_index(&registerStates, minUsedRegisterIndex))->baseOffset, globalIROut);

    return _SUCCESS_;
}






//Parse an expression
RETURN_CODE internal_parse_expression(Vector *tokens, size_t indexStart, RegisterData *destRegMetadata) {


    if(tokens == NULL || destRegMetadata == NULL) {
        return _INVALID_ARG_PASS_;
    }
    //NOTE: Order matters
    //x = x*3 IS NOT THE SAME as x = 3*x
    //Second case sets x = 3 first then does 3*3 = 9, First case does x = x, then x = x*3

    //NOTE: Automatically saves registers before overwritting them
    //If not in registers, load from stack


    //Expect num, op, num, op, ...
    


    //TODO:
    //Set up source and destination registers
    //Should be based on how much its been used
    //Save the register that is pushed out to its stack address



    size_t accumulatorRegister = -1;

    
    if(destRegMetadata->registerNumber == -1) { //If variable not in register, load it into a register
        //Request a empty register
        if(internal_push_into_registers(destRegMetadata, -1) != _SUCCESS_) {
            return _INTERNAL_ERROR_;
        }
        accumulatorRegister = destRegMetadata->registerNumber;
    }
    size_t regDestination = destRegMetadata->registerNumber;



    Token *currentToken = NULL;
    bool expectOperator = false;
    VALID_TOKEN_ENUM prevOp = TOK_ADD;


    for(size_t i = indexStart; i < vector_get_length(tokens) + 1; i++) {
        currentToken = (Token*)vector_get_index(tokens, i);
        if(currentToken == NULL) {
            return _INTERNAL_ERROR_;
        }
        if(expectOperator == true) {
            if(i == indexStart + 1) {
                prevOp = currentToken->tokenEnum;
                continue; //This is really unoptimised
            }

            switch (prevOp) {
            case TOK_ADD:
                internal_macro_addition(regDestination, accumulatorRegister, globalIROut);
                break;
            case TOK_SUB:
                internal_macro_subtraction(regDestination, accumulatorRegister, globalIROut);
                break;
            case TOK_MUL:
                internal_macro_multiplication(regDestination, accumulatorRegister, globalIROut);
                break;
            case TOK_DIV:
                internal_macro_division(regDestination, accumulatorRegister, globalIROut);
                break;
            case EOF_TOKEN:
                return _SUCCESS_;
                break;

            default:
                printf("Expected operator - ");
                return _INVALID_ARG_PASS_;
                break;
            }
            prevOp = currentToken->tokenEnum;

        } else {


            switch (currentToken->tokenEnum) {
            case USER_STRING: {

                //If variable not in register, load it from memory into the temp register
                const char *varToLoad = dynamic_string_read(&(currentToken->userString));
                RegisterData *currentLoadVariable = (RegisterData*)string_hashmap_get_value(&variableStorage, (void*)varToLoad, strlen(varToLoad));

                if(currentLoadVariable == NULL) {

                    printf("Variable '%s' not defined - ", varToLoad);
                    return _INVALID_ARG_PASS_;

                } else if(currentLoadVariable->registerNumber == -1) { //Load into register
                    if(internal_push_into_registers(currentLoadVariable, regDestination) != _SUCCESS_) {
                        return _INTERNAL_ERROR_;
                    }
                    internal_macro_load(destRegMetadata->registerNumber, destRegMetadata->baseOffset, globalIROut);
                
                } else {
                    accumulatorRegister = currentLoadVariable->registerNumber;
                }
            }

                break;
            case INT_IMMEDIATE:
                //Should optimise this later so that immediates can directly be used with add/sub/mul/div instructions
                //Check in operator branch if previous/nextitem is an immediate, if so then use immediate arithmatic instructions


                //Request a free register for the immediate
                if(internal_request_immediate_register(&accumulatorRegister, regDestination) != _SUCCESS_) {
                    return _INTERNAL_ERROR_;
                }

                internal_macro_load_immediate(accumulatorRegister, currentToken->intImmediate, globalIROut);
                break;

            default:
                printf("Expected operand - ");
                return _INVALID_ARG_PASS_;
                break;
            }

        }

        expectOperator = !expectOperator;
    }




    return _SUCCESS_;
}







//Parse a 'set' statement
RETURN_CODE internal_parse_set(Vector *tokens) {

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
    RegisterData *varWriteMetadata = (RegisterData*)string_hashmap_get_value(&variableStorage, (void*)variableStr, strlen(variableStr) + 1);
    if(varWriteMetadata == NULL) {
        printf("Undeclared variable '%s' - ", variableStr);
        return _INTERNAL_ERROR_;
    }


    //Assert '='
    internal_macro_assert_token(tokens, 2, TOK_EQUALS_ASSIGNMENT, "Expected '='", tokenOut);



    //Calculate expression
    //Write the result to wherever the variable is stored
    RETURN_CODE returnVal = internal_parse_expression(tokens, 3, varWriteMetadata);
    if(returnVal != _SUCCESS_) {
        return _INVALID_ARG_PASS_;
    }

    //Assert ';'
    //internal_macro_assert_token(tokens, 3, TOK_SEMICOLEN, "Expected ';'", tokenOut);

    return _SUCCESS_;
}








//Parse declaration of a value
RETURN_CODE internal_parse_dec(Vector *tokens) {

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
    RegisterData *varWriteMetadata = (RegisterData*)string_hashmap_get_value(&variableStorage, (void*)variableStr, strlen(variableStr));
    if(varWriteMetadata != NULL) {
        printf("Redeclaration of variable '%s' - ", variableStr);
        return _INTERNAL_ERROR_;
    }

    RegisterData newVariableMetadata;
    newVariableMetadata.baseOffset = nextFreebaseOffset;
    nextFreebaseOffset += STACK_DATASIZE;
    newVariableMetadata.registerNumber = -1; //Specify new variable is not in a register
    newVariableMetadata.timesRequested = 0;
    newVariableMetadata.inUse = true;


    //Assert '='
    internal_macro_assert_token(tokens, 2, TOK_EQUALS_ASSIGNMENT, "Expected '='", tokenOut);

    //Calculate expression
    //Write the result to wherever the variable is stored
    RETURN_CODE returnVal = internal_parse_expression(tokens, 3, &newVariableMetadata);
    if(returnVal != _SUCCESS_) {
        return _INVALID_ARG_PASS_;
    }


    //Add new variable to hashmap
    if(string_hashmap_set(&variableStorage, variableStr, strlen(variableStr) + 1, &newVariableMetadata, sizeof(RegisterData)) == false) {
        return _INTERNAL_ERROR_;
    }

    //Assert ';'
    //internal_macro_assert_token(tokens, 3, TOK_SEMICOLEN, "Expected ';'", tokenOut);


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
    if(vector_initialise(&registerStates, sizeof(RegisterData)) != true) {
        return _INTERNAL_ERROR_;
    }

    RegisterData padding;
    padding.inUse = false;
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













