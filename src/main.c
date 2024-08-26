#include "tokenise.h"
#include "parse.h"

#define TOKEN_PATH "./data/test_tokens.txt"
#define IR_PATH "./data/IR.txt"
#define SRC_BUFFER_SIZE 1000

int main(void) {

    Vector tokensOut;


    char lineInputBuffer[SRC_BUFFER_SIZE];

    FILE *fptrSrc = fopen(TOKEN_PATH, "r");
    FILE *fptrDst = fopen(IR_PATH, "w");

    if(fptrSrc == NULL) {
        printf("Failed to open src file\n");
        return 1;
    }
    if(fptrDst == NULL) {
        printf("Failed to open dest file\n");
        return 1;
    }



    if(parse_initialise() != _SUCCESS_) {
        printf("Failed to initialise parser\n");
        return 1;
    }

    for(size_t i = 0; fgets(lineInputBuffer, SRC_BUFFER_SIZE, fptrSrc) != NULL; i++) {

        if(tokenise(lineInputBuffer, &tokensOut) != _SUCCESS_) {
            
            printf("Error occured on line %zu\n", i);
            return 1;
        }


        /*
        printf("\n\n");
        if(print_tokens(&tokensOut) != _SUCCESS_) {

            printf("Failed to print tokens\n");
            return 1;
        }
        printf("\n\n");
        */

       if(parse(&tokensOut, fptrDst) != _SUCCESS_) {
            printf("Line error: %zu\n", i);
            return 1;
        }
    }
    
    return 0;
}














