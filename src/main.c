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


    Queue q1;
    queue_initialise(&q1, sizeof(int));

    for(int i = 0; i < 10; i++) {
        if(queue_enqueue(&q1, &i) == false) {
            printf("Failed to enqueue\n");
            return -1;
        }
    }

    printf("\n\n");
    int *ptr = NULL;

    for(int i = 0; i < 10; i++) {

        if(queue_dequeue(&q1, (void*)ptr) == false) {

            printf("Failed to dequeue");
            return false;
        }

        printf("%d, ", *ptr);

    }


    queue_print(&q1);

    return 0;
}














