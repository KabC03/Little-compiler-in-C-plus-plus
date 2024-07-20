#include "VM.h"
#include "tokenise.h"
#include "parse.h"

#define TOKEN_PATH "./data/test_tokens.txt"
#define IR_PATH "./data/IR.txt"

int main(void) {

    /*
    Vector tokensOut;

    if(tokenise(TOKEN_PATH, &tokensOut) != _SUCCESS_) {
        
        printf("Failed to tokenise\n");
        return -1;
    }
    if(print_tokens(&tokensOut) != _SUCCESS_) {

        printf("Failed to print tokens\n");
        return -2;
    }

    if(parse(&tokensOut, IR_PATH) != _SUCCESS_) {

        printf("Failed to parse tokens\n");
        return -3;
    }
    */

    LinkedList l1;
    LL_initialise(&l1, sizeof(int));

    for(int i = 0; i < 10; i++) {
        printf("i = %d\n",i);
        if(LL_insert_index(&l1, i, &i) == false) {
            printf("Failed to insert\n");
            return -1;
        }
    }


    
    if(LL_print(&l1) == false) {
        printf("Failed to print\n");
    }

    return 0;
}














