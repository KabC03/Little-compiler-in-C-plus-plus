
# Intermediate representation


## Introduction

The intermediate representation (IR) is an intermediate assembly-like language used in the compiler.


It is produced from source code by the compiler and can either be turned into architecture dependednt assembly (and assembled into machine code) or intepreted on the IR virtual machine directly.




## Syntax and functionality


### Form
All assembly instructions take the form:

    [OPCODE] [ARG1] [ARG2] [ARG3]

- (R)egister type instructions have three operands
    - Opcode, destination register, source register, source register

- (I)mmediate type instructions have three operands
    - Opcode, register, register, immediate

- (J)ump type instructions have one operand
    - Opcode, label

- (A)bstracted type instructions may have any amount of operands in any configuration
    - These instructions are present in the IR as placeholders for functions often involving system calls


### Registers

- The IR considers only general purpose registers and a stack pointer and are addressed as follows:
    - General purpose: 
        - R0, R1, R2, ...
    - Stack pointer:
        - RS
    - Zero (always zero):
        - RZ

- The number of general purpose registers must be specified before compilation



### Abstracted instructions

To remain architecture independent, the IR contains placeholder instructions that represent system call operations.

These instructions are not classified under the same R, I, J types as other instructions

When architecture specific assembly is produced from the IR, these instrucions are replaced with the target systems call procedures (often system calls).

The IR virtual machine has its own system calls that map to C functions


##### Below: Rx - register, Ix - immediate, Lx - label, _x - F/I depending on whether operation occurs on float or integer

- INPUT_x R0

    - Request input from the terminal and store the result into R0


- OUTPUT_x R0

    - Print the value contained within R0 to the termi

- ALLOCATE R0 R1

    - Requests a block of memory of size (R1) in bytes and places a pointer to its first element into (R0)
    - If allocation fails R0 is set to 0
    - The size of the block is put into the first element of the array as an unsigned number
        - On the IR virtual machine the datatype of this size type must be specified during initialisation

- FREE R0

    - Mark memory pointed to by R0 as free

- SLEEP R0

    - Pauses execution and sleeps for R0 microseconds



- PARALLEL_START I0

    - Marks the instructions below it to be executed in parallel by a CPU core with ID (I0)

- PARALLEL_STOP

    - Stops the current CPU core executing a block in parallel causing it to idle indefinitely

- SYNC I0

    - Synchronises CPU cores by pausing execution until all cores executing a program with the ID of (I0) reach their SYNC instruction with the same ID of (I0)





### Instructions


##### Below: Rx - register, Ix - immediate, Lx - label, _x - F/I depending on whether operation occurs on float or integer



##### Misc

- NOP
    - No operation
    - Does nothing for one clock cycle


##### Memory

- LOAD_x R0 I0 R1
    - Load the address stored in (R0) with offset (I0) bytes into R1

- STORE_x R0 I0 R1
    - Store contents of (R0) into the address (R1) with offset (I0)

##### Arithmatic instructions

- ADD_x R0 R1 R2
    - Add contents of (R1) and (R2) and place the result into R0 

- SUB_x R0 R1 R2
    - Subtract contents of (R2) from (R1) and place the result into (R0)

- MUL_x R0 R1 R2
    - Multiply contents of (R1) and (R2) and place the result into (R0)

- DIV_x R0 R1 R2
    - Divide contents of (R1) and (R2) and place the result into (R0)

- MOD_x R0 R1 R2
    - Take the modulus of (R1) and (R2) and place the result into (R0)


- ADDI_x R0 R1 I0 
    - Add contents of (R1) and (R0) and place the result into (R0)

- SUBI_x R0 R1 I0
    - Subtract contents of (R2) from (R0) and place the result into (R0)

- MULI_x R0 R1 I0
    - Multiply contents of (R1) and (I0) and place the result into (R0)

- DIVI_x R0 R1 I0
    - Divide contents of (R1) and (I0) and place the result into (R0)

- MODI_x R0 R1 I0
    - Take the modulus of (R1) and (I0) and place the result into (R0)


##### Jump instructions

- BEQ_x R0 R1 Lx
    - If (R0) == (R1) jump to Lx

- BLT_x R0 R1 Lx
    - If (R0) < (R1) jump to Lx

- BLE_x R0 R1 Lx
    - If (R0) <= (R1) jump to Lx


- JAL Lx
    - Jump and link
    - Jumps to label (Lx) after pushing current program counter address onto the stack

- JRT
    - Jump return
    - Jumps to the address on the top of the stack (thereby removing it)

- JUMP Lx
    - Jump unconditionally to label (Lx)




#### Note:

Only float and integer datatypes are expected

Characters/unsigned datatypes are not directly supported


