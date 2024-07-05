#include "parse.h"



size_t globalBranchID;              //Used to keep track of the last label ID (to prevent two labels having the same ID and wrong jumps)
size_t globalVariableID;            //Used to keep track of the last label ID (to prevent two labels having the same ID and wrong jumps)


//Metadata for variables - held within the current stack frame
typedef struct VariableMetadata {

    TOKEN_TYPE datatype;                  //int, float, chat, etc
    size_t indirectionlvel;               //level of indirection (number of '@')
    size_t stackoffset;                   //offset from current base pointer (NOTE: offset defined in IR but not anything else)

} variablemetadata;

//Metadata for if, elif, else, for, while, etc statements
typedef struct JumpMetadata {

    size_t branchID;                       //e.g beq R1 R2 branchID (label ID)
    size_t returnID;                       //At the end of an elif block when wanting to skip over next elif (label ID)
                                    
    bool expectingOpenBrace;               //Used to denote that a '{' is expected (end of if statement) on the next line as the first token
    bool seenIf;                           //Used to make sure elif or else is not declared before an if

    //Statement should consume nex } token it sees

} JumpMetadata;

//Metadata for the current function (pushed onto an internal stack for functions)
typedef struct FunctionMetadata {

    size_t currentFrameSize;              //Sum of local variables and arguments (here for debugging)
    size_t numberOfLocalVariables;        //Number of local variables
    size_t expectedNumberArgumesnts;      //Expected number of arguments
    StringHashmap localVariables;         //Hashmap of local variables (key = variabl name, value = VariableMetadata)
    Stack JumpMetadata;                   //Metadata for jumps (holds address for successful and non-successful jumps)

} FunctionMetadata;



typedef struct ProgramFlowMetadata {

    bool mainIsDefined;                   //Main function has been seen
    bool insideFunction;                  //Used to make sure a function is not declared inside another function
    bool writtenMainJump;                 //Used to record if the first time call 'jump main' has been set

} ProgramFlowMetadata;

//Use these directly
StringHashmap functionMetadata;           //Hashmap of func name to metadata - add to it as functions are defined
ProgramFlowMetadata programFlowMetadata;  //Metadata for program progression
Stack currentFunctionStack;               //Stack of the currently used functions - used to trace the frame

/*

E.g:

SOURCE CODE:

fn func(a) {

    b = a;
    c = b + a;

    return c;
}

fn main() {

    a = func(10);
}





IR:
label func(a)

SET B
B = A

SET C
LET acc 0
ADD acc, B, A


ret C





label main()

SET A

push A //Push A onto the stack
push 2 //Push space for 2 variables onto the stack
update //Update any variables (e.g Store them in RAM if the register one is more updated than RAM)
call func()
pop 2
pop A

//NOTE: Use RPN to evaluate expressions just using one accumulator
//Also note: Before calling function always make sure variables are up to date before pushing
*/




/*

- If first call, write 'jum main' (unconditional jump to main function)
- Next expecting a function declaration (no global variables)
    - Main function takes no arguments but always returns an integer


- By end of the program at least one main function should have been seen


*/





/**
 * parser_initialise 
 * ===============================================
 * Brief: Parse a line of tokens 
 * 
 * Param: void
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
bool parser_initialise(void) {

    if(stack_initialise(&currentFunctionStack, sizeof(FunctionMetadata)) == false) {
        return false;
    }
    
    if(string_hashmap_initialise(&functionMetadata, INITIAL_MAP_SIZE) == false) {
        return false;
    }

    programFlowMetadata.insideFunction = false;
    programFlowMetadata.mainIsDefined = false;
    programFlowMetadata.writtenMainJump = false;

    return true;
}


/**
 * parse 
 * ===============================================
 * Brief: Parse a line of tokens 
 * 
 * Param: *tokens - Token array (NULL to indicate EOF)
 *        *IRFilePtr - Pointer to an opened file ptr destination (in append mode)
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
bool parse(Vector *tokens, FILE *IRFilePtr) {

    if(IRFilePtr == NULL) {
        return false;
    } else {

        //If first token is of specific marker then know its the end of the source file
        //Write call to main here
        if(tokens == NULL) {

            const FunctionMetadata *mainFunctionMetadata = string_hashmap_get_value(&functionMetadata, IR_MAIN_FUNC_NAME, strlen(IR_MAIN_FUNC_NAME) + 1);
            if(mainFunctionMetadata == NULL) {
                printf("Failed to find main funcion\n");
                return false;
            }
            
            fprintf("    %s %zu\n", IR_STACK_RESERVE, mainFunctionMetadata->numberOfLocalVariables);

        } else {


        }
    }

    return true;
}










