#include "parse.h"



size_t globalBranchID;              //Used to keep track of the last label ID (to prevent two labels having the same ID and wrong jumps)
size_t globalVariableID;            //Used to keep track of the last label ID (to prevent two labels having the same ID and wrong jumps)




//Metadata for variables - held within the current stack frame
typedef struct VariableMetadata {

    token_type datatype;                  //int, float, chat, etc
    size_t indirectionlvel;               //level of indirection (number of '@')
    size_t stackoffset;                   //offset from current base pointer

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

    size_t currentFrameSize;              //Frame size of LOCAL variables
    StringHashmap localVariables;         //Hashmap of local variables (key = variabl name, value = VariableMetadata)
    Stack JumpMetadata;                   //Metadata for jumps (holds address for successful and non-successful jumps)

} FunctionMetadata;



typedef struct ProgramFlowMetadata {

    bool mainIsDefined;                   //Main function has been seen
    bool insideFunction;                  //Used to make sure a function is not declared inside another function
    bool writtenmainJump;                 //Used to record if the first time call 'jump main' has been set

} ProgramFlowMetadata;

//Use these two directly
Stack functionMetadata;                   //Stack of function metadata
ProgramFlowMetadata programFlowMetadata;  //Metadata for program progression

/*

- If first call, write 'jum main' (unconditional jump to main function)
- Next expecting a function declaration (no global variables)
    - Main function takes no arguments but always returns an integer


- By end of the program at least one main function should have been seen


*/






