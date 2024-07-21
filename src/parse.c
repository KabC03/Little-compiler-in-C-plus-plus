//20, Jun, 2024
#include "parse.h"

bool allowedToExit = false;                   //If allowed to exit (if in the middle of a declaration cannot exit)
#define LOCAL_HASHMAP_SIZE 100                //Local hashmap size for function and variable metadatas
#define SIZEOF_INTEGER 4
#define SIZEOF_FLOAT 4
#define SIZEOF_CHAR 4 //Should be 1 - to match UTF-8 but chose 4 so that its always memory aligned


//Assert a single token (like ; at the end of a statement) - Also increments counter automatically
#define internal_assert_token(INPUT_TOKENS, INPUT_TOKEN_INDEX, TOKEN_ASSERTED, SYMBOL_ASSERTED) \
	/*SYMBOL - The symbol actually expected e.g - <*/\
	/*INPUT_TOKEN_INDEX - Index into inputTokens*/\
	/*INPUT_TOKENS - Vector of tokens*/\
	do {\
		const Token *currentToken = vector_get_index(INPUT_TOKENS, INPUT_TOKEN_INDEX);\
		if(currentToken == NULL) {\
			return _INTERNAL_ERROR_; /*Should never happen*/\
		}\
		if(currentToken->tokenEnum != TOKEN_ASSERTED) { /*Check if the symbols are equal*/\
			printf("Expected '%s'\n", SYMBOL_ASSERTED);\
			return _INVALID_ARG_PASS_;\
		}\
		INPUT_TOKEN_INDEX++; /*Increment the counter*/\
	} while(0);





//Metadata
typedef struct VariableMetadata {

	size_t offsetFromBasePointer;             //Offset from stack base pointer
	size_t numberOfCallsToVariable;           //How many times this variable has been requested (used to decide who to push out of a register when one is neeeded)
	size_t variableLocationInRegister;        //Register number containing the variable - if not contained then set this to 0
	//Static type checking 
	size_t indirectionLevel;                  //Number of @
	VALID_TOKEN_ENUM baseType;                //Base datatype (e.g char, float, int, etc)

} VariableMetadata;
StringHashmap functionNameToMetadataMap;
bool validEndOfTokenStream = false;           //Used to denote if it is correct to exit the program now (e.g main is defined, not in the middle of a statement)
bool mainIsDefined = false;                   //Used to denote if main function has been defined or not
typedef struct FunctionMetadata {

	StringHashmap variableNameToMetadataMap;  //Variable name to its metadata for the current function
	size_t numberOfVariables;                 //Used to keep track of the top of the stack from base pointer
	Stack jumpMetadata;                       //Metadata for any jumps (labels)
	//Static type checking
	VariableMetadata returnTypeMetadata;      //Metadata for the return type

} FunctionMetadata;
typedef struct JumpMetadata {

	size_t labelID;                           //Label ID to write at the end of the if statement (preceded with a '.' to avoid collisions)

} JumpMetadata;


//Print a single token
RETURN_CODE internal_print_tokens(const Token *currentToken) {

	const char *userStringOut = NULL;
	if(currentToken == NULL) {
		return _INVALID_ARG_PASS_;

	} else {

		if(currentToken == NULL) {
			printf("CANNOT OBTAIN TOKEN\n");
			return _INTERNAL_ERROR_;
		}

		switch (currentToken->tokenEnum) {
		case EOF_TOKEN:
			printf("EOF\n");
			break;
		case INT_IMMEDIATE:
			printf("%d",currentToken->intImmediate);
			break;
		case FLOAT_IMMEDIATE:
			printf("%f",currentToken->floatImmediate);
			break;
		case CHAR_IMMEDIATE:
			printf("%c",currentToken->charImmediate);
			break;
		case USER_STRING:

			userStringOut = dynamic_string_read(&(currentToken->userString));
			if(userStringOut == NULL) {
				printf("CANNOT OBTAIN STRING TOKENAL ERROR\n");
				return _INTERNAL_ERROR_;
			}
			printf("%s",userStringOut);
			break;
		default:
			break;
		}

		printf("%s", validTokens[currentToken->tokenEnum]);


		return _SUCCESS_;
	}

	return _INTERNAL_ERROR_;
}




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

    Token *popToken = NULL;
    const Token *peakToken = NULL;
	bool expectingOperator = false; //Used to specify if an operator or symbol is expected
	const Token *currentToken = NULL;
	while(1) {
		//Loop until a non-arithmatic or operator is found (includes EOF token)

		currentToken = (Token*)vector_get_index(tokens, *startIndex); 
		if(currentToken == NULL) {
			return _INTERNAL_ERROR_;
		}
        (*startIndex)++;

		//Deal with parenthesis first
		switch(currentToken->tokenEnum) {

			case TOK_OPEN_PAREN:
		 
                if(stack_push(&operatorStack, &currentToken) == false) {
                    return _INTERNAL_ERROR_;
                }
				expectingOperator = false; //Expecting a value or parenthesis next
				continue;

			case TOK_CLOSE_PAREN:
                
                //Pop until a matching open paren is found in the operator stack
                while(1) {

                    if(stack_pop(&operatorStack, (void*)(&popToken)) == false) {
                        return _INTERNAL_ERROR_;
                    }
                    if(popToken == NULL) {
                        return _INVALID_ARG_PASS_;
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
                



				expectingOperator = false; //Expecting a value or parenthesis next
				break;



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
                        return _INVALID_ARG_PASS_; //Means saw a operator first before any variables
                    }
                        free(popToken);

                    //Push higher precedence operator onto stack
                    if(peakToken->tokenEnum != TOK_ADD && peakToken->tokenEnum != TOK_SUB) {
                        if(stack_push(&operatorStack, peakToken) == false) { 
                            return _INTERNAL_ERROR_;
                        }

                    } else {
                        //Push current token onto stack and exit
                        if(stack_push(&operatorStack, &currentToken) == false) { 
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
                if(stack_push(&operatorStack, &currentToken) == false) {
                    return _INTERNAL_ERROR_;
                }
				continue;     

			
			default:
		return _SUCCESS_;
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
				printf("Expected a value but recieved: '");
				internal_print_tokens(currentToken);
				printf("'\n");
			}


		}

	}


	return _SUCCESS_;
}





/**
 * parse
 * ===============================================
 * Brief: Parses an input vector of tokens and outputs IR
 * 
 * Param: *tokens - Tokens to parse 
 *        *irOutputFileName - File name to output to
 *
 *
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
RETURN_CODE parse(Vector *tokens, char *irOutputFileName) {


	if(tokens == NULL || irOutputFileName == NULL) {

		return _INVALID_ARG_PASS_;
	}

	//Setup stuff
	FILE *irOutputFilePtr = fopen(irOutputFileName, "w");
	if(irOutputFileName == NULL) {
		
		return _FILE_NOT_OPENED_;
	}
	fprintf(irOutputFilePtr, "::::::\n");



	//TEMPORARY
	size_t index = 0;
	Queue q1;
	queue_initialise(&q1, sizeof(Token));
	if(internal_shunting_yard_algorithm(tokens, &index, &q1) != _SUCCESS_) {
		printf("SYA failed\n");
		return -1;
	}
	printf("\n\n");

	Token *token;
	while(1) {
		if(queue_dequeue(&q1, (void*)(&token)) == false) {
			break;
		}

		internal_print_tokens(token);
		printf(", ");
	}
	printf("\n\n");
	return _SUCCESS_;



	//Read the stream of tokens
	//First token will immediatly tell what type of operation it is

	for(size_t i = 0; ;i++) {

		//Get the newest token
		const Token *currentToken = (Token*)vector_get_index(tokens, i); 
		if(currentToken == NULL) {
			return _INTERNAL_ERROR_;
		}

		
		//Switch it to see what it is - call corrosponding function
		//i acts like a program counter (can go back or forth depending on what is to be parsed
		switch(currentToken->tokenEnum) {

			case EOF_TOKEN:
				//End of token stream reached
				if(allowedToExit == true) {
					//Check if was in the middle of declaring something
					return _SUCCESS_; 
				} else {
					printf("Statement incomplete\n");
					return _INVALID_ARG_PASS_;
				}
				break;


		   

			case TOK_FN:
				//Function declaration

				break;
			
			case TOK_RET:
				//Return keyword

				break;





			case TOK_LBL:
				//Label declaration

				break;

			case TOK_GTO:
				//Goto statement

				break;




			case TOK_OPEN_ANGLE:
				//Variable declaration

				break;


			case TOK_IF:
				//If statement

				break;





			default:


				//Check for a function or variable name
				//Function - Call to a void function
				//Variable name - A reassignment
				//If neither then not a valid first token


				printf("Starting token was not recognised: '");
				internal_print_tokens(currentToken);
				printf("'\n");

				return _INVALID_ARG_PASS_;



		}
	}

	return _SUCCESS_;
}

















































