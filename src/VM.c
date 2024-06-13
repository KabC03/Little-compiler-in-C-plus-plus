#include "VM.h"
#define array_len(array) sizeof(array)/sizeof(array[0])
#define current_instruction ((VirtualMachine.instructionMemory)[i])


#define RAM_TYPE uint8_t
#define INSTRUCTION_MEMORY_EXPANSION 10
#define INSTRUCTION_INPUT_BUFFER 100


typedef enum OPCODE {

    END, //USED TO DENOTE END OF TOKEN STREAM - NOT PART OF ISA

    ADD_I,
    SUB_I,
    MUL_I,
    DIV_I,

    ADD_F,
    SUB_F,
    MUL_F,
    DIV_F,

    SHL,
    SHR,

    AND,
    OR,
    NOT,

    LOD,
    STR,

    BEQ,
    BLT,
    BLE,

    JUM,

    JAL,
    CAL,

} OPCODE;
typedef enum OPCODE_TYPE {

    NONE,
    INTEGER,
    FLOAT,

} OPCODE_TYPE;
typedef enum INSTRUCTION_TYPE {

    R,
    I,
    J,
    A,

} INSTRUCTION_TYPE;


typedef struct Instruction {
    
    INSTRUCTION_TYPE instructionType;

    OPCODE opcode;
    OPCODE_TYPE opcodeType;

    size_t reg0;
    size_t reg1;

    union ARG3 {
        char *label;
        float floatImmediate;
        int intImmediate;
        size_t reg2;
    } ARG3;

} Instruction;
typedef union Registers {

    int intValue;
    float floatValue;

} Registers;


struct VM {

    size_t programCounter;             //Program counter index into instructionMemory

    Registers *registers;              //Pointer to register array

    Instruction *instructionMemory;    //Array of instructions
    RAM_TYPE *RAM;                      //Bytes

};




VM VirtualMachine; //Only ONE should exist
bool initialise_VM(size_t numberOfRegisters, size_t sizeOfRam) {

    if(numberOfRegisters == 0 || sizeOfRam == 0) {
        printf("Number of registers or size of RAM cannot be zero\n");
        return false;
    }

    VirtualMachine.registers = malloc(numberOfRegisters * sizeof(Registers));
    VirtualMachine.RAM = malloc(sizeOfRam * sizeof(RAM_TYPE));
    VirtualMachine.instructionMemory = NULL;
    VirtualMachine.programCounter = 0;

    if(VirtualMachine.registers == NULL || VirtualMachine.RAM == NULL) {
        printf("Unable to allocate space for registers or RAM\n");
        return false;
    }


    return true;
}


bool destroy_VM(void) {
    //Free memory associated with VM
    if(VirtualMachine.registers != NULL) {
        free(VirtualMachine.registers);
    }
    if(VirtualMachine.RAM != NULL) {
        free(VirtualMachine.RAM);
    }
    if(VirtualMachine.instructionMemory != NULL) {

        for(int i = 0; current_instruction.opcode != END; i++) {
            if(current_instruction.instructionType == I) {

            } else if(current_instruction.instructionType == J) {
                
            }
        }
    }
    return true;
}



bool get_tokens_VM(char *IRfileName) {

    if(IRfileName == NULL) {
        printf("Filename unexpectedly NULL\n");
        return false;
    }

    FILE *IRfile = fopen(IRfileName, "r");
    if(IRfile == NULL) {
        printf("Unable to open '%s'\n",IRfileName);
        return false;
    }

    char instructionInputBuffer[INSTRUCTION_INPUT_BUFFER];

    //Note: programCounter being used TEMPORARILY to keep track of the instructionMemory size
    VirtualMachine.programCounter = 0;
    char *currentToken = NULL;
    for(size_t i = 0; fgets(instructionInputBuffer, array_len(instructionInputBuffer), IRfile); i++) {

        if(i == VirtualMachine.programCounter) { //Reallocate memory
            VirtualMachine.instructionMemory = realloc(VirtualMachine.instructionMemory, VirtualMachine.programCounter + INSTRUCTION_MEMORY_EXPANSION); //NEED TO HANDLE IF REALLOC FAILS
            if(VirtualMachine.instructionMemory == NULL) {
                printf("Memory allocation failure when expanding instruction memory\n");
                return false;
            }
            VirtualMachine.programCounter += INSTRUCTION_MEMORY_EXPANSION;
        }

        //Get instruction type
        currentToken = strtok(instructionInputBuffer, " \n");
        if(currentToken == NULL) { //Empty line
            continue;
        }
        
        if(strcmp(currentToken, "[R]") == 0) {
            current_instruction.instructionType = R;
        } else if(strcmp(currentToken, "[I]") == 0) {
            current_instruction.instructionType = I;
        } else if(strcmp(currentToken, "[J]") == 0) {
            current_instruction.instructionType = J;
        } else if(strcmp(currentToken, "[A]") == 0) {
            current_instruction.instructionType = A;
        } else { //Unrecognised instruction type
            printf("Unrecognised instruction '%s'\n",currentToken);
            return false;
        }


        //Continue




    }
    




    //Cleanup
    fclose(IRfile);
    VirtualMachine.programCounter = 0;
    return true;
}

































































































































