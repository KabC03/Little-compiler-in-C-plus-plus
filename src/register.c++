#include "register.h++"


/**
 * register_push 
 * ===============================================
 * Brief: Push a variable/immediate to a register - operandMap must be updated seperately
 * 
 * Param: 
 *        &parserData - Parser data struct to adjust
 *        &operand - Operand to write
 * 
 * Return: bool 
 * 
 */
bool register_push(ParserData &parserData, Operand &operand) {

    //Look for a free space


    if(operand.registerIndex != -1 && operand.isFree == false) {
        return true;
    }


    auto min = parserData.registerStates.begin();
    for(auto it = parserData.registerStates.begin(); it != parserData.registerStates.end(); it++) {

        if((*it).isFree == true) { //Found a free space
            min = it;
            break;
        } else if((*min).timesRequested > (*it).timesRequested) { //Search for minimum
            min = it;
        }
    }

    //Convert iterator to index
    auto index = distance(parserData.registerStates.begin(), min);

    //Save position
    if((*min).isFree == false) { //Variable
        macro_pneumonic_save(index, (*min).memoryOffset, parserData.outputFile);
        //Update position in hashmap
        (*min).registerIndex = -1; //Indicate variable was pushed out of registers
    }
    
    operand.registerIndex = index;
    if(operand.isFree == true) {
        macro_pneumonic_load_immediate(operand.registerIndex, operand.immediate, parserData.outputFile);
    } else {
        macro_pneumonic_load(operand.registerIndex, operand.memoryOffset, parserData.outputFile);
        operand.timesRequested++;
        operand.registerIndex = index;
    }

    (*min) = operand; //Put into register 
    return true;
}






