//30 Aug 2024
#include <fstream>
#include "compiler data.h++"
#include "tokenise.h++"
#include "parse.h++"
#define SRC_FILE_PATH "./data/test_tokens.txt"
#define OUTPUT_FILE_PATH "./data/IR.txt"

using namespace std;


int main(void) {


    //debug_tokenise_map_print(tokenMap);

    //File handling
    ifstream srcFile(SRC_FILE_PATH);
    ofstream outputFile(OUTPUT_FILE_PATH);
    string inputString = "\0";
    int returnValue = 0;

    //Initialise structures
    auto tokenMap = tokeniser_initialise_map();
    auto parserData = parser_initialise(outputFile);

    if(srcFile.is_open() == false) {
        cout << "ERROR: Unable to open source file" << endl;
        returnValue = 1;
    }
    if(outputFile.is_open() == false) {
        cout << "ERROR: Unable to open output file" << endl;
        returnValue = 2;
    }

    for(size_t i = 0; getline(srcFile, inputString); i++) { //Read line by line
        vector<Token> tokeniserOut = tokeniser_tokenise(inputString, tokenMap);
        if(tokeniserOut.size() == 0) {
            cout << "Line:" << i << endl;
            returnValue = 3;
            break; //Error in tokeniser
        }
        //debug_tokenise_tokens_print(tokensOut);
        if(parser_parse(tokeniserOut, parserData) == false) {
            cout << "Line:" << i << endl;
            returnValue = 4;
            break; //Error in parser
        }

    }


    outputFile.close();
    srcFile.close();

    return returnValue;
}
























