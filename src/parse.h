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




/*
Parser flow 2:

- Go to main function first
- As variables are declared push them onto the stack
    - Store their stack address in a dictionary (name -> address) for the function
- This is called function metadata (dictionary + name of function etc)
- This allows for nested calls
- Push and pop function metadata when functions are called - allowing the compiler to keep track of the current called function
- This also means variables can be defined anywhere - not nesseserily in a program section, functions can be written/called anywhere too
    - Preface function declaration with 'fn' and variable declaration with 'dec'

- Function metadata stores
    - key value for variable name and offset from base pointer for current stack frame
    - Type for each variable in the frame
    - Number of variables in the stack frame
    - Should push/pop metadata as functions are called and returned from


- Steps
    - First parser call -> write 'jump main' (unconditional jump to main function)
    - Second and onwards -> Look at first word
        - If its a } then pop from if statement stack thingy (as normal)
        - If its a keyword then set relevent flags for later (e.g - if fn then in function mode)
            - Use this to ensure grammer beween lines (e.g have to FINISH declaring the function)
        - If its whitespace just ignore
*/




/*

Parser flow:

- ALWAYS look at the first token
    - If its a } then you must pop from the jump address stack and put a label there
    - This is because } symbolises the end of a conditional statement

- Next look at the following token

    -Directives
        - If its a directive (e.g $program$ or $function$ or $data$) then change the data mode
        - Must change directives in this order:
        - none -> $data$ -> $function$ -> $program$ 
            - Note $function does not have to be present
        - Cannot go back (e.g if in $program$ cannot go back to $data$ and declare more variables)
        - Set the current mode flag - thiswill determine what can and cannot be done in the following lines (e.g can ONLY declare functions in $function$)

    - Logic
        - Look at the token - it tells you what the line does
        - E.g for, if, elif, while, etc
        - These will tell you immediatly the structure of the IR. Its just a case of putting the actual expressions into the template
        - While matching, make sure grammer is correct
        - If in a conditional statement, a { must be present as the last token or the next one on the newline (use a flag for this)
        - Push if statement jump (at end) onto the stack
            - Dont pop if there is an elif/else below, only pop if there isnt one
            - This stack must be maintained seperately to the other conditional stack
            - Also allows for nested conditions

    - Expressions
        - Expressions must be evaluated recursively with precedence
        - Includes arithmatic, dereferencing and function calls



    - Declarations should add a variable to a dictionary (key = variable -> value = type)
        - Types are used for arithmatic (e.g float and int addition instructions are different)
        - Strict type checking is enforced, cannot do arithmatic on float and int/char (but can do with char and int together since char is basically an int) 

    - Labels should be an ID and then jumped to
        - E.g If in a conditional statement, jump to label with ID 1, ID 1 is put onto the stack of addresses and a label is placed when a } is found

    - Functions should put their address into a dictionary which can be referenced by its name
        - Max args to a function is enforced in IR->asm (here set it to the number of registers)
        - Argumets include any temporary variables used by the function (this is because a function is limited to the current registers - it cannot load from RAM)
            - Variables cannot be declared inside a declaration function body
        - All argumeents are PASSED BY REFERENCE (not value), meaning the stack is not used

    - IR->asm converter will place variables into the registers themselves and perform small peephole optimisations (e.g if jump and label follow eachother remove the jump)
        - No other optimisations will be implemented - only those of the fault of the compiler itself (e.g poorly timed load/store operations)


    - Any syntax errors or unexpected tokens should immediatly cause the parser to report an error (and the token that caused it)
*/



/*

IDEA 3:


- In parser (generating IR)

- IR references stack but not general purpose registers
- When calling function push space for functions local variables onto stack and then push arguments on
- This will lead to a small amount of bloat
- After function call pop off out of


label func (a,b,c) {

    //Do something requiring 2 temp variables
}

main:

push a
push b
push c
push space 2
call func
pop space 5 (total space)

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
#define INITIAL_MAP_SIZE 100


bool parser_initialise(void);
bool parse(Vector *tokens, DynamicString *outputString);



#endif // PARSE_H




