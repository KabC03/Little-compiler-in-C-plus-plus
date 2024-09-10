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



bool parser_initialise(string outputFilePath, ParserData &parserData);
bool parser_parse(vector<Token> &tokens, ParserData &parserData);



#endif //PARSE_HH







