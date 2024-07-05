 #include "parse.h"



size_t globalBranchID;              //Used to keep track of the last label ID (to prevent two labels having the same ID and wrong jumps)
size_t globalVariableID;            //Used to keep track of the last label ID (to prevent two labels having the same ID and wrong jumps)




//Metadata for variables - held within the current stack frame
typedef struct VariableMetadata {

    TOKEN_TYPE dataType;             //int, float, chat, etc
    size_t indirectionLvel;          //Level of indirection (number of '@')
    size_t stackOffset;              //Offset from current base pointer

} VariableMetadata;

//Metadata for if, elif, else, for, while, etc statements
typedef struct JumpMetadata {

    size_t branchID;                 //e.g beq R1 R2 branchID (label ID)
    size_t returnID;                 //At the end of an elif block when wanting to skip over next elif (label ID)

} JumpMetadata;

//Metadata for the current function (pushed onto an internal stack for functions)
typedef struct FunctionMetadata {

    size_t currentFrameSize;         //Frame size of LOCAL variables
    StringHashmap localVariables;    //Hashmap of local variables (key = variabl name, value = VariableMetadata)
    Stack JumpMetadata;              //Metadata for jumps (holds address for successful and non-successful jumps)

} FunctionMetadata;



Stack functionMetadata;              //Stack of function metadata










