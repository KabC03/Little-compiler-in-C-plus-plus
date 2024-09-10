#include "register.h++"


/**
 * register_push 
 * ===============================================
 * Brief: Push a variable/immediate to a register - operandMap must be updated seperately
 * 
 * Param: 
 *        &parserData - Parser data struct to adjust
 *        &outputFile - Output file to write to
 *        &operand - Operand to write
 * 
 * Return: bool 
 * 
 */
bool register_push(ParserData &parserData, ofstream &outputFile, Operand &operand) {

    //Look for a free space

    auto min = parserData.registerStates.begin();
    for(auto it = parserData.registerStates.begin(); it != parserData.registerStates.end(); it++) {

        if((*it).varID == 0) { //Found a free space
            break;
        } else if((*min).timesRequested > (*it).timesRequested) { //Search for minimum
            min = it;
        }
    }

    //Convert iterator to index
    auto index = distance(parserData.registerStates.begin(), min);

    //Save position
    if((*min).varID != 0) {
        macro_pneumonic_save(index, (*min).memoryOffset, outputFile);
    }
    
    //Write to the new position
    operand.registerIndex = index;

    if(operand.varID == 0) {
        macro_pneumonic_load_immediate(operand.registerIndex, operand.immediate, outputFile);
    } else {
        macro_pneumonic_load(operand.registerIndex, operand.memoryOffset, outputFile);
        operand.timesRequested++;
    }

    (*min) = operand;
    return true;
}






