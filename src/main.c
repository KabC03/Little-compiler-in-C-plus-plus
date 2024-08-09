#include "VM.h"
#include "tokenise.h"
#include "parse.h"

#define TOKEN_PATH "./data/test_tokens.txt"
#define IR_PATH "./data/IR.txt"
#define SRC_BUFFER_SIZE 1000

int main(void) {

    Vector tokensOut;


    char lineInputBuffer[SRC_BUFFER_SIZE];

    FILE *fptr = fopen(TOKEN_PATH, "r");
    if(fptr == NULL) {
        printf("Failed to open src file\n");
        return -1;
    }


    for(size_t i = 0; fgets(lineInputBuffer, SRC_BUFFER_SIZE, fptr) != NULL; i++) {

        if(tokenise(lineInputBuffer, &tokensOut) != _SUCCESS_) {
            
            printf("Error occured on line %zu\n", i);
            return -2;
        }
        /*
        if(print_tokens(&tokensOut) != _SUCCESS_) {

            printf("Failed to print tokens\n");
            return -3;
        }
        */

       if(parse(&tokensOut) != _SUCCESS_) {
            printf("Error occured on line %zu\n", i);
            return -3;
        }
    }
    
    return 0;
}














