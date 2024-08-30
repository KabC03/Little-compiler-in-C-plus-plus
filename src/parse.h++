//30 Aug 2024
#ifndef PARSE_HH
#define PARSE_HH




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
#include "compiler data.h++"
#include "tokenise.h++"
#include "architecture pneumonics.h++"
using namespace std;


typedef struct Operand {

    string varName;      //Variable name
    size_t memoryOffset; //Memory offset from base

    bool isVar;          //If false, can overwrite this register space

} Operand;
typedef struct ParserStructures {
    vector<Operand> registerStates;             //Track items in register
    unordered_map<string, Operand> operandMap;  //Track known variables
    unordered_set<string> knownLabels;          //Track known labels
    ofstream outputFile;                        //Output file
    stack<string> ifStack;                      //Stack to track if statement depth, contains labels
} ParserStructures;

ParserStructures parser_initialise(ofstream &outputFileSet);
bool parser_parse(vector<Token> &tokens, ParserStructures &parserStructures);



#endif //PARSE_HH







