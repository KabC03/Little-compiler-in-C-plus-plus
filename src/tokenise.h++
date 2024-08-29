//30 Aug 2024
#ifndef TOKENISE_HH
#define TOKENISE_HH


#define NUMBER_OF_TOKENS 19
#define MAX_TOKEN_LENGTH 8

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cerrno>
#include <iomanip>
#include <cctype>
#include "compiler data.h++"
using namespace std;


void debug_tokenise_map_print(unordered_map<string, int> &tokenMap);
void debug_tokenise_tokens_print(vector<Token> &tokens);
unordered_map<string, int> tokeniser_initialise_map(void);
vector<Token> tokeniser_tokenise(const string &inputString, unordered_map<string, int> &tokenMap);



#endif //COMPILER_DATA_HH







