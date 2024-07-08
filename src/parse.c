#include "parse.h"


typedef struct FunctionMetadata {

    DynamicString functionName;              //Name of the function (same as the key)
    Stack conditionalJumpMetadata;           //A stack of all conditional jump data
    StringHashmap variableMetadata;          //Hashmap of variable name -> variable metadata 

} functionMetadata;
typedef struct ConditionalJumpMetadata {

    Token statementType;                     //Type of statement (while, for, if, etc)
    DynamicString labelIfSkipped;            //Label to exit the statement beq R1 R2 label <- this label
    DynamicString labelIfRun;                //Label to go to if the statement is run j label <- this label
    DynamicString loopLabel;                 //Label to loop back to the start of the statement

} ConditionalJumpMetadata;
typedef struct VariableMetadata {

    DynamicString variableName;              //Name of the variable (same as key)
    Token type;                              //Type of the variable (char, float, int)
    size_t indirectionLevel;                 //Pointer indirection level
    size_t offsetFromBasePtr;                //How far the variable is stored from the base pointer of the current frame + 1 (account for return address)

} VariableMetadata;


StringHashmap functionNameToMetadata;        //Hashmap of all known functions that are defined -> function metadata
functionMetadata *currentFunctionProccessed; //Pointer to the current function being processed


/**
 * parse 
 * ===============================================
 * Brief: parses a line of code, outputs lines of IR 
 * 
 * Param: *tokens - Input token array 
 *        *irFile - Output text file for IR (Open file pointer)
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
bool parse(Vector *tokens, FILE *irFile) {

    if(tokens == NULL || irFile == NULL) {
        return false;
    }




    






    return true;
}






