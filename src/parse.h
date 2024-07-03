//Parser


/*
How it works

- Get an array of tokens
- First token tells you what to do (e.g if, for, while, etc)
- Based on this can figure out what kind of IR to generate - just fill in variable names and stuff

- Use a stack for nested conditionals
- First or last token might be a '{' or '}'
- This is just from an above if statement - tells the compiler to pop something off the stack (put a jump label) - and continue as normal
*/

#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>





#endif // PARSE_H






