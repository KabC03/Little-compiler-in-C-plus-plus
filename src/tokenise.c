#include "tokenise.h"


int main(void) {

    FILE *sourceFilePtr = fopen("src.txt", "r");
    if(sourceFilePtr == NULL) {
        return -1;;
    }


    Vector tokenVector;
    if(vector_initialise(&tokenVector, sizeof(Token)) == false) {
        return -1;
    }
    char lineBuffer[MAX_LINE_LENGTH];



    bool containsSymbols = false;
    bool containsNumbers = false;
    bool containsLetters = false; 
    while(fgets(lineBuffer, sizeof(lineBuffer)/sizeof(lineBuffer[0]), sourceFilePtr)) {

        //Add tokens to a buffer then hash
        //Depending on next character  and if token contains symbols, numbers, letters (e.g ' ') decide if the token is complete so move onto the next

            

    }




    fclose(sourceFilePtr);

    return 0;
}




