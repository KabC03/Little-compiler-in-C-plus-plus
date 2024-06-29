#include "compiler data.h"
#include "datastructures.h"
#include "hashmap.h"
#include "vector.h"


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

    while(fgets(lineBuffer, sizeof(lineBuffer)/sizeof(lineBuffer[0]), sourceFilePtr)) {

        

    }




    fclose(sourceFilePtr);

    return 0;
}

