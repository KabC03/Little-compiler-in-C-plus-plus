//Dump of the shunting yard algorithm from the parser - useless for the compiler

//Shunting yard algorithm for ordering tokens - note outputQueue should be destroyed by consumer (but initialised) of token stack
RETURN_CODE internal_shunting_yard_algorithm(Vector *tokens, size_t *startIndex, Queue *outputQueue) {

	if(tokens == NULL || startIndex == NULL || outputQueue == NULL) {
		return _INVALID_ARG_PASS_;
	}

	//Expressions: +,-,*,/,==,!=,>>,etc
	//Must check expression is one of these, then parse
  

	Stack operatorStack;
	if(stack_initialise(&operatorStack, sizeof(Token)) == false) {
		return _INTERNAL_ERROR_;
	}

	size_t stackLength;
    Token *popToken = NULL;
    const Token *peakToken = NULL;
	bool expectingOperator = false; //Used to specify if an operator or symbol is expected
	const Token *currentToken = NULL;
	while(1) {
		//Loop until a non-arithmatic or operator is found (includes EOF token)
		//printf("Here\n");
		currentToken = (Token*)vector_get_index(tokens, *startIndex); 
		if(currentToken == NULL) {
			return _INTERNAL_ERROR_;
		}
        (*startIndex)++;

		//Deal with parenthesis first
		switch(currentToken->tokenEnum) {

			case TOK_OPEN_PAREN:
		 
                if(stack_push(&operatorStack, currentToken) == false) {
                    return _INTERNAL_ERROR_;
                }
				continue;

			case TOK_CLOSE_PAREN:
                
                //Pop until a matching open paren is found in the operator stack
                while(1) {

                    if(stack_pop(&operatorStack, (void**)(&popToken)) == false) {
                        return _INTERNAL_ERROR_; 
                    }
                    if(popToken == NULL) {

                        return _INVALID_ARG_PASS_; //No matching (
                    }
                    
                    if(popToken->tokenEnum == TOK_OPEN_PAREN) {
                        //Disguard the paren
                        free(popToken);
                        break;

                    } else {
                        //Push onto operator stack
                        if(queue_enqueue(outputQueue, popToken) == false) {

                            return _INTERNAL_ERROR_;
                        }
                        free(popToken);
                    }
                }
				continue;;



            default:
                break;
		}


		if(expectingOperator == true) {
			expectingOperator = false;
			switch(currentToken->tokenEnum) {

            //Add and sub have same precedence
			case TOK_ADD: 
			case TOK_SUB: 

                while(1) {
                    peakToken = stack_peak(&operatorStack);
                    if(peakToken == NULL) {
						//First operator declared
                        if(stack_push(&operatorStack, currentToken) == false) { 
                            return _INTERNAL_ERROR_;
                        }

                        break;
                    
					} else if(peakToken->tokenEnum != TOK_ADD && peakToken->tokenEnum != TOK_SUB && peakToken->tokenEnum != TOK_OPEN_PAREN) {
                    	//Push higher precedence operator onto stack

						if(stack_pop(&operatorStack, (void**)(&popToken)) == false) {
							return _INTERNAL_ERROR_;
						}
						if(popToken == NULL) {
							return _INVALID_ARG_PASS_;
						}
						if(queue_enqueue(outputQueue, popToken) == false) {
							return _INTERNAL_ERROR_;
						}
						free(popToken);

                    } else {
                        //Push current token onto stack and exit
                        if(stack_push(&operatorStack, currentToken) == false) { 
                            return _INTERNAL_ERROR_;
                        }
                        break;
                    }

                }


				continue;     



            //These all have the same precedence
			case TOK_MUL: 
			case TOK_DIV: 
			case TOK_MOD: 
                //Assumed to have highest precedence
                if(stack_push(&operatorStack, currentToken) == false) {
                    return _INTERNAL_ERROR_;
                }
				continue;     

			
			default:
				break;
			}


		} else {
			expectingOperator = true;
			switch(currentToken->tokenEnum) {

			case INT_IMMEDIATE:
			case FLOAT_IMMEDIATE:
			case CHAR_IMMEDIATE:
			case USER_STRING:
			if(queue_enqueue(outputQueue, currentToken) == false) {
				queue_destroy(outputQueue);
				return _INTERNAL_ERROR_;
			}
                continue;
			default:

				break;
				/*
				printf("Expected a value but recieved: '");
				internal_print_tokens(currentToken);
				printf("'\n");
				return _INVALID_ARG_PASS_;
				*/
			}


		}


		//Pop off all items from stack and enqueue
		stackLength = stack_length(&operatorStack);
		for(size_t i = 0; i < stackLength; i++)	{
			if(stack_pop(&operatorStack, (void**)(&popToken)) == false) {
				return _INTERNAL_ERROR_;
			}

		
			if(popToken == NULL) {
				return _INVALID_ARG_PASS_;
			}
			if(queue_enqueue(outputQueue, (void*)popToken) == false) {
				return _INTERNAL_ERROR_;
			}
			free(popToken);
		}
		
		return _SUCCESS_;



	}


	return _SUCCESS_;
}



