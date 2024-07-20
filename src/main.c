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

    int data = 10;
    LL_insert_index(&l1, 0, &data);
    LL_print(&l1);

    return 0;
}














