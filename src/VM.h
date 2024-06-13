#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <signal.h>



typedef struct VM VM;



bool initialise_VM(size_t numberOfRegisters, size_t sizeOfRam, size_t stackSize);
bool get_tokens_VM(char *IRfileName);
bool run_VM(void);




