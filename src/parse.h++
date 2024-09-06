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
#include "register.h++"
using namespace std;


typedef struct ParserData {
    vector<Operand> registerStates;             //Track items in register
    unordered_map<string, Operand> operandMap;  //Track known variables
    unordered_set<string> knownLabels;          //Track known labels
    ofstream outputFile;                        //Output file
    stack<string> ifStack;                      //Stack to track if statement depth, contains labels
} ParserData;

bool parser_initialise(string outputFilePath, ParserData &parserData);
bool parser_parse(vector<Token> &tokens, ParserData &parserData);



#endif //PARSE_HH







