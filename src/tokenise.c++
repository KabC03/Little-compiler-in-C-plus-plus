//30 Aug 2024
#include "tokenise.h++"
#define TOKEN_VECTOR_RESERVE 10
#define TOKEN_STRING_WINDOW_RESERVE 5




//Print key::value pairs in token map
void debug_tokenise_map_print(unordered_map<string, int> &tokenMap) {

    for(auto i = tokenMap.begin(); i != tokenMap.end(); i++) {
        cout << "Key:" << setw(10) << i->first << " ||| Value: " <<  setw(10) << i->second << endl;
    }

    return;
}



//Print a single token
void debug_tokenise_singular_token_print(Token &token) {


    switch(token.tokenType) {//Int immediate/string will have negative index

    case TOK_IMM_INT: {
        cout << "Type: TOK_IMM" << endl;
        break;
    } case TOK_STRING: {
        cout << "Type: TOK_STRING" << endl;
        break;
    } default: {
        cout << "Type: " << setw(10) << validTokens[token.tokenType] << endl; //Enum can directly index into token array
        break;
    }
    }
    cout << "\tImm: " << setw(10) << token.immInt << endl;
    cout << "\tStr: " << setw(10) << token.string << endl;
    cout << endl;

    return;
}


//Print a token vector
void debug_tokenise_tokens_print(vector<Token> &tokens) {

    cout << "---Tokens: " << tokens.size() << "---" << endl;
    for(auto i = tokens.begin(); i != tokens.end(); i++) {

        debug_tokenise_singular_token_print((*i));
    }

    return;
}




/**
 * tokeniser_initialise_map 
 * ===============================================
 * Brief: Initialises internal tokeniser structures, call once in main
 * 
 * Param: 
 *         srcFilePath
 * 
 * Return: TokeniserData
 * 
 */
TokeniserData tokeniser_initialise_map(string srcFilePath) {

    TokeniserData tokenData;

    tokenData.inputFile.open(srcFilePath);
    if(tokenData.inputFile.is_open() == false) {
        cout << "ERROR: Unable to open source file" << endl;
    }
    for(int i = 0; i < NUMBER_OF_TOKENS; i++) {

        tokenData.tokenMap[validTokens[i]] = i;
    }
    
    return tokenData;
}



/**
 * tokeniser_tokenise
 * ===============================================
 * Brief: Tokenise an input string
 * 
 * Param: 
 *        &inputString - Input string to be tokenised
*         &tokenData - Token data to be used to validate tokens
 * 
 * Return: tokens - Vector of output tokens
 * 
 */
vector<Token> tokeniser_tokenise(const string &inputString, TokeniserData &tokenData) {

    //Reserve some space to avoid resizing
    string stringWindow = "\0";
    stringWindow.reserve(TOKEN_STRING_WINDOW_RESERVE);
    vector<Token> outputTokensVector = {};
    outputTokensVector.reserve(TOKEN_VECTOR_RESERVE); 


    int j = 0;
    bool endOfToken = false;

    Token newToken;
    for(auto i = inputString.begin(); i != inputString.end(); i++, j++) { //Maybe unsafe... (OOB access)
        

        newToken.immInt = INT_MAX;
        newToken.string = "INV";
        newToken.tokenType = TOK_INVALID;

        //Window can only contain tokens of same type (e.g 'jim', '++', '12345')
        if(isspace(*i) == true) {
            continue;

        } else if(ispunct(*i) == true && ispunct(*(i+1)) == false) {
            endOfToken = true;

        } else if(isdigit(*i) == true && isdigit(*(i+1)) == false) {
            endOfToken = true;

        } else if (isalpha(*i) == true && isalpha(*(i+1)) == false) {
            endOfToken = true;

        }

        stringWindow += *i;
        if(endOfToken == true) {


            auto mapIterator = tokenData.tokenMap.find(stringWindow);
            if(mapIterator != tokenData.tokenMap.end()) { //Keyword found
                newToken.tokenType = (TOKEN_TYPE)mapIterator->second; 
                //Cast to int so the compiler doesnt complain


            } else {

                //Since all tokens garunteed to be all char or all numbers can just check the first char
                if(stringWindow.size() == 0) {
                    cout << "ERROR: stringWindow is unexpectedly zero length" << endl;
                    return {};

                } else if(isalpha(stringWindow[0]) == true) { //Variable
                    newToken.tokenType = TOK_STRING;
                    newToken.string = stringWindow;

                } else if(isdigit(stringWindow[0]) == true) { //Immediate
                    newToken.tokenType = TOK_IMM_INT;
                    newToken.immInt = stoi(stringWindow);

                } else {
                    cout << "ERROR: unexpected recognised string '" << stringWindow << "'" << endl;
                    return {};
                }

            }
            outputTokensVector.push_back(newToken);
            stringWindow.clear();
            endOfToken = false;
        }
        
    }

    //Similar to '\0' in C
    newToken.immInt = INT_MAX;
    newToken.string = "INV";
    newToken.tokenType = TOK_END_OF_STREAM;
    outputTokensVector.push_back(newToken);

    return outputTokensVector;
}



































