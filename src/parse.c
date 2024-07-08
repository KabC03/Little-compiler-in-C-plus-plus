#include "parse.h"

typedef struct ProgramMetadata {

    bool mainIsDefined;                      //If main is defined
    bool expectingFirstTokenAsOpenbrace;     //Expect the first token on next line to be a {
    bool expectingFirstTokenAsClosebrace;    //Expect the first token on next line to be a }
    bool currentlyInsideFunction;            //If currently parsing a function

    bool requestJumpLabel;                   //Flag set to true if a jump label should be placed immedietly from the conditionalJumpMetadata

} ProgramMetadata;




typedef struct FunctionMetadata {

    DynamicString functionName;              //Name of the function (same as the key)
    Stack conditionalJumpMetadata;           //A stack of all conditional jump data
    StringHashmap variableMetadata;          //Hashmap of variable name -> variable metadata 

} FunctionMetadata;
typedef struct ConditionalJumpMetadata {

    TOKEN_TYPE statementType;                //Type of statement (while, if, etc)
    size_t labelSkipStatement;               //Label to exit the statement beq R1 R2 label <- this label
    size_t labelEndOfStatement;              //Label to go to if the statement is run j label <- this label (while)
    size_t labelStartOfStatement;            //Label to loop back to the start of the statement
    bool curleyBraceWasOpened;               //If a { appears
    bool elifOrElseWasEncountered;           //If an elif or else was encountered (used to avoid placing unnesesary jumps)
    //NOTE: For loops no longer supported


} ConditionalJumpMetadata;
typedef struct VariableMetadata {

    DynamicString variableName;              //Name of the variable (same as key)
    TOKEN_TYPE type;                         //Type of the variable (char, float, int)
    size_t indirectionLevel;                 //Pointer indirection level
    size_t offsetFromBasePtr;                //How far the variable is stored from the base pointer of the current frame + 1 (account for return address)

} VariableMetadata;


StringHashmap functionNameToMetadata;        //Hashmap of all known functions that are defined -> function metadata
FunctionMetadata *currentFunctionProccessed; //Pointer to the current function being processed (NULL if no function)
ProgramMetadata programMetadata;             //Struct holding basic data for the entire program
size_t globalLabelCounter = 0;               //Global label counter
FILE *globalIRFileOutput = NULL;                   //Pointer to an open file pointer







//Parse an array of tokens that is a function declaration
bool parse_function_declaration(Vector *tokens) {

    if(vector_get_length(tokens) < 3) {
        printf("Function declaration expects more than 3 tokens\n");
        return false;
    }
    
    //Continue here

    


    return true;
}















//If the first token is a { or }, handle it accordingly, otherwise return false - return -1 to indicate syntax error, 0 to indicate braces parsed and 1 to indicate no braces parsed
ERROR_CODES handle_first_brace(Vector *tokens) {

    if(tokens == NULL) {
        return _NULL_PTR_PASS_;
    } else {

        const Token *firstTokenInTokens = (Token*)vector_get_index(tokens, 0);




        if(firstTokenInTokens->Token == OPEN_CURLEY) {

            if(programMetadata.currentlyInsideFunction == true) {


                //Make sure a if statement was actually declared
                if(stack_length(&(currentFunctionProccessed->conditionalJumpMetadata)) == 0) {
                    printf("Expected a jump statement declaration\n");
                    return _GENERIC_FAILURE_;
                }

                ConditionalJumpMetadata *currentJumpMetadata = stack_peak(&(currentFunctionProccessed->conditionalJumpMetadata));
                if(currentJumpMetadata->curleyBraceWasOpened == true) {

                    //If a brace was already opened previously
                    printf("Unexpected additional '{' encounteded\n");
                    return _GENERIC_FAILURE_;
                    
                } else {
                    //Mark the brace as opened - note compiler will only notice brace not closed at next if block
                    currentJumpMetadata->curleyBraceWasOpened = true;
                }


            } else {
                printf("Expected a function declaration\n");
                return _GENERIC_FAILURE_;
            }
            programMetadata.expectingFirstTokenAsOpenbrace = false;

        } else if(firstTokenInTokens->Token == CLOSE_CURLEY) {

            
            //Make sure a if statement was actually declared
            if(stack_length(&(currentFunctionProccessed->conditionalJumpMetadata)) == 0) {
                printf("Expected a jump statement declaration\n");
                return _GENERIC_FAILURE_;
            }

            ConditionalJumpMetadata *currentJumpMetadata = stack_peak(&(currentFunctionProccessed->conditionalJumpMetadata));

            if(currentJumpMetadata == NULL)  {
                printf("Unexpectedly not able to get stack data\n");
                return _GENERIC_FAILURE_;
            }


            if(currentJumpMetadata->curleyBraceWasOpened == false) {

                //Make sure that the statement was opened with a '{'
                printf("Expected a '{'\n");
                return _GENERIC_FAILURE_;
                
            } else {
                //Depending on statement type may need to do a variety of things
                //While loop -> jump to start label
                //If statement -> Write a jump over the next elif and else 

                if(currentJumpMetadata->statementType == COND_IF 
                || currentJumpMetadata->statementType == COND_ELIF) {

                    //If the next token is not an elif then write the jump label
                    programMetadata.requestJumpLabel = true;
                
                } else if(currentJumpMetadata->statementType == COND_ELSE) {

                    //Can write jump label
                    size_t labelToJumpTo = currentJumpMetadata->labelEndOfStatement;
                    fprintf(globalIRFileOutput, "    %s %zu\n", IR_LABEL, labelToJumpTo);
                    //Write the label to jump to

                } else if(currentJumpMetadata->statementType == COND_WHILE) {

                    size_t restartLoopLabel = currentJumpMetadata->labelStartOfStatement;
                    size_t jumpOutOfLoopLabel = currentJumpMetadata->labelEndOfStatement;

                    fprintf(globalIRFileOutput, "    %s %zu\n", IR_JUMP_UNCONDITIONAL, restartLoopLabel);
                    fprintf(globalIRFileOutput, "    %s %zu\n", IR_LABEL, jumpOutOfLoopLabel);

                    //Write jump back to start and label to quite white loop
                } else {
                    printf("Expected conditional statement\n");
                    return _GENERIC_FAILURE_;
                }


            }
            programMetadata.expectingFirstTokenAsClosebrace = false;

        } else {
            return _NEUTRAL_; 
        }
        return _SUCCESS_;

    }


    return _GENERIC_FAILURE_;
}


//Write conditional jumps for if, elif depending on if flag is set
bool write_if_elif_jumps(Token *token) {

    if(token->Token == COND_ELIF) {
        return true; //Do nothing
    } else {

        //Write the jump address
        ConditionalJumpMetadata *currentJumpMetadata = stack_peak(&(currentFunctionProccessed->conditionalJumpMetadata));
        if(currentJumpMetadata == NULL)  {
            printf("Unexpectedly not able to get stack data\n");
            return false;
        }
        if(currentJumpMetadata->elifOrElseWasEncountered == false) {

            //Dont do anything - unessesary jump
        } else {

            size_t labelToJumpTo = currentJumpMetadata->labelEndOfStatement;
            fprintf(globalIRFileOutput, "    %s %zu\n", IR_LABEL, labelToJumpTo);
            
        }

        //Pop the statement off the stack
        void *ptr = NULL; //Pass a NULL ptr to indicate pop value should not be returned
        if(stack_pop(&(currentFunctionProccessed->conditionalJumpMetadata), ptr) == false) {
            printf("Was not able to pop off stack unexpectedly\n");
            return false;
        }
    }

    return false;
}



/**
 * parser_initialise_structures 
 * ===============================================
 * Brief: Initialises the parsers structures before use 
 * 
 * Param: *irFile - Output text file for IR (Open file pointer)
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
bool parser_initialise_structures(FILE *irFile) {



    if(string_hashmap_initialise(&(functionNameToMetadata), INITIAL_MAP_SIZE) == false) {
        printf("Failed to initialise parser hashmap\n");
        return false;
    }
    currentFunctionProccessed = NULL;
    programMetadata.currentlyInsideFunction = false;
    programMetadata.expectingFirstTokenAsClosebrace = false;
    programMetadata.expectingFirstTokenAsOpenbrace = false;
    programMetadata.mainIsDefined = false;
    programMetadata.requestJumpLabel = false;
    globalLabelCounter = 0;
    globalIRFileOutput = irFile;



    return true;
}




/**
 * parse 
 * ===============================================
 * Brief: parses a line of code, outputs lines of IR 
 * 
 * Param: *tokens - Input token array 
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
bool parse(Vector *tokens) {

    if(tokens == NULL) {
        return false;
    }


    size_t sizeOfInputTokens = vector_get_size(tokens);

    if(sizeOfInputTokens == 0) {
        
        printf("Parser error: Expected token to contain more than zero items\n");
        return false;
    }


    Token *firstTokenOfInterest = NULL;


    //Handle braces
    ERROR_CODES handleFirstBraceReturn = handle_first_brace(tokens);
    if(handleFirstBraceReturn == _SUCCESS_) { //Could use T/F directly but dont want to rely on that

        if(sizeOfInputTokens == 1) {
            return true; //Exit early - this indicates a free { or } was encountered
        }

        //Otherwise set the token of interest to the one afterwards
        firstTokenOfInterest = (Token*)vector_get_index(tokens, 1);

    } else if(handleFirstBraceReturn == _NEUTRAL_) {


        if(programMetadata.expectingFirstTokenAsOpenbrace == false) {
            printf("Expected a '{'\n");
            return false;
        }


        firstTokenOfInterest = (Token*)vector_get_index(tokens, 0);
    } else { //Syntax error encountered
        return false;
    }


    //Handle any previous jumps that should have occured
    if(write_if_elif_jumps(firstTokenOfInterest) == false) {
        return false;
    }

    
    if(firstTokenOfInterest->Token == FUNC_DECL) {

        //Declare a function
        if(parse_function_declaration(tokens) == false) {
            return false;
        }
    }





    return true;
}





