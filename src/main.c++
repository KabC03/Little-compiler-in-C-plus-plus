//30 Aug 2024
#include "compiler data.h++"
#include "tokenise.h++"




int main(void) {
    auto tokenMap = tokeniser_initialise_map();

    //debug_tokenise_print(tokenMap);
    string input = "int 199";
    vector<Token> tokensOut = tokeniser_tokenise(input, tokenMap);
    debug_tokenise_tokens_print(tokensOut);

    return 0;
}
























