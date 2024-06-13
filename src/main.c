#include "VM.h"


int main(void) {


    initialise_VM(10, 100, 10);
    if(get_tokens_VM("IR.txt") == false) {
        return -1;
    }
    run_VM();





    return 0;
}














