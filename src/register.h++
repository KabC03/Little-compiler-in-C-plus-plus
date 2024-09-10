#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cerrno>
#include <fstream>
#include <stack>
#include <unordered_set>
#include <iomanip>
#include <cctype>
#include "architecture pneumonics.h++"

using namespace std;

typedef struct Operand {

    int varID;             //ID of variable - value of 0 indicates free position
    size_t memoryOffset;   //Memory offset from base
    int registerIndex;  //Index of register item is in (-1 if not in register)
    size_t timesRequested; //Times a variable has been requested
    int immediate; //Immediate

} Operand;

typedef struct ParserData {
    vector<Operand> registerStates;             //Track items in register
    unordered_map<string, Operand> operandMap;  //Track known variables
    unordered_set<string> knownLabels;          //Track known labels
    ofstream outputFile;                        //Output file
    stack<string> ifStack;                      //Stack to track if statement depth, contains labels
} ParserData;

bool register_push(ParserData &parserData, ofstream &outputFile, Operand &operand);


#endif //REGISTER_H




