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

//Print a token vector
void debug_tokenise_tokens_print(vector<Token> &tokens) {

    for(auto i = tokens.begin(); i != tokens.end(); i++) {
        cout << "Type: " << setw(10) << validTokens[(*i).tokenType] << endl; //Enum can directly index into token array
        cout << "\tImm: " << setw(10) << (*i).immInt << endl;
        cout << "\tStr: " << setw(10) << (*i).string << endl;
        cout << endl;
    }

    return;
}




/**
 * tokeniser_initialise_map 
 * ===============================================
 * Brief: Initialises internal tokeniser structures, call once in main
 * 
 * Param: 
 *        void
 * 
 * Return: tokenMap - Token map associating string::TOKEN_TYPE
 * 
 */
unordered_map<string, int> tokeniser_initialise_map(void) {

    unordered_map<string, int> tokenMap;
    for(int i = 0; i < NUMBER_OF_TOKENS; i++) {

        tokenMap[validTokens[i]] = i;
    }

    return tokenMap;
}




/**
 * tokeniser_tokenise
 * ===============================================
 * Brief: Tokenise an input string
 * 
 * Param: 
 *        inputString - Input string to be tokenised
 * 
 * Return: tokens - Vector of output tokens
 * 
 */
vector<Token> tokeniser_tokenise(const string &inputString, unordered_map<string, int> &tokenMap) {

    //Reserve some space to avoid resizing
    string stringWindow = "\0";
    stringWindow.reserve(TOKEN_STRING_WINDOW_RESERVE);
    vector<Token> outputTokensVector = {};
    outputTokensVector.reserve(TOKEN_VECTOR_RESERVE); 


    int j = 0;
    bool endOfToken = false;
    for(auto i = inputString.begin(); i != inputString.end(); i++, j++) {
        
        Token newToken;
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

            auto hashWindow = tokenMap.find(stringWindow);
            if(hashWindow != tokenMap.end()) { //Keyword found
                newToken.tokenType = (TOKEN_TYPE)hashWindow->second; 
                //Cast to int so the compiler doesnt complain
                outputTokensVector.push_back(newToken);

            } else {

                //Since all tokens garunteed to be all char or all numbers can just check the first char
                if(stringWindow.size() == 0) {
                    cout << "ERROR: stringWindow is unexpectedly zero length" << endl;
                    return {};

                } else if(isalpha(stringWindow[0]) == true) { //Variable
                    newToken.string = stringWindow;

                } else if(isdigit(stringWindow[0]) == true) { //Immediate
                    newToken.immInt = stoi(stringWindow);

                } else {
                    cout << "ERROR: unexpected recognised string '" << stringWindow << "'" << endl;
                    return {};
                }

            }
            
            stringWindow.clear();
            endOfToken = false;
        }
        
    }


    return outputTokensVector;
}



































