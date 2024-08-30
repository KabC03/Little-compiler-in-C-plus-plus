//30 Aug 2024
#ifndef TOKENISE_HH
#define TOKENISE_HH


#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cerrno>
#include <iomanip>
#include <fstream>
#include <cctype>
#include "compiler data.h++"
using namespace std;

typedef struct TokeniserData {

    unordered_map<string, int> tokenMap;
    ifstream inputFile;

} TokeniserData;

void debug_tokenise_map_print(unordered_map<string, int> &tokenMap);
void debug_tokenise_singular_token_print(Token &token);
void debug_tokenise_tokens_print(vector<Token> &tokens);
TokeniserData tokeniser_initialise_map(string srcFilePath);
vector<Token> tokeniser_tokenise(const string &inputString, TokeniserData &tokenData);



#endif //TOKENISE_HH







