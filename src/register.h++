#ifndef REGISTER_H
#define REGISTER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <iterator>
#include <fstream>
#include "architecture pneumonics.h++"

using namespace std;

typedef struct Operand {

    int varID;             //ID of variable - value of 0 indicates free position
    size_t memoryOffset;   //Memory offset from base
    size_t registerIndex;  //Index of register item is in (0 if not in register)
    size_t timesRequested; //Times a variable has been requested
    int immediate; //Immediate

} Operand;

bool register_push(vector<Operand> &registers, ofstream &outputFile, Operand &operand);


#endif //REGISTER_H




