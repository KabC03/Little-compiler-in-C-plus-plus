//Parser


/*
HOW IT WORKS
- Input tokens are directly mapped to IR output
- Get an array of tokens
- First token tells you what to do (e.g if, for, while, etc)
- Based on this can figure out what kind of IR to generate - just fill in variable names and stuff
- Parser has no idea of any program context before or after the current line, other than the dictionary and stack mentioned below

IF STATEMENTS
- Use a stack for nested conditionals
- First or last token might be a '{' or '}'
- This is just from an above if statement - tells the compiler to pop something off the stack (put a jump label) - and continue as normal


- NOTE: Use variables themselves here, dont try to put things into registers yet

- Need to parse recursively expressions

PROGRAM:
- In program section
- Hash all variable names and give them a register number


- In function section
- If there is no function section, skip everything
- Hash all function names and give them an address to jump to
- Create a main function and write a 'jump main' at the top to skip all functions


- In program section
- Parse more complex logical structures




IR -> ASM
- IR output can be further mapped to architecture specific assembly
- Put variables into actual registers
- Keep a counter of how much a variable is requested from a register
- When it comes to store a new variable into a register, push the least used value out
- Perform some peephole optimisation (elimiate useless instruction combinations)




ASM -> Machine code
- Either use NASM or code up a basic assembler
- Shouldnt be too bad since the compiler probably wont use many cisc instructions
*/

#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"
#include "datastructures.h"
#include "static hashmap.h"
#include "string hashmap.h"
#include "compiler data.h"
#include "tokenise.h"


bool parse(Vector *tokens);


#endif // PARSE_H






