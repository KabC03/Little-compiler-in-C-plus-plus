#include "VM.h"
#define array_len(array) sizeof(array)/sizeof(array[0])
#define current_instruction ((VirtualMachine.instructionMemory)[i])


#define RAM_TYPE uint8_t
#define INSTRUCTION_MEMORY_EXPANSION 1
#define LABEL_EXPANSION 1
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

    LOD,
    STR,

    BEQ,
    BLT,
    BLE,

    JUM,

    JAL,
    CAL,

    ALLOC, //A type function (basically malloc)
    FREE,  //A type function (basically free)

    LABEL, //NOT an instruction - used to declare labels

} OPCODE;
typedef enum INSTRUCTION_TYPE {

    R, //Register
    I, //Immediate
    C, //Compare
    J, //Jump
    A, //Abstract
    L, //Label

} INSTRUCTION_TYPE;
typedef enum OPCODE_DATATYPE {

    INTEGER,
    FLOAT,
    NONE,

} OPCODE_DATATYPE;


typedef struct Instruction {
    
    INSTRUCTION_TYPE instructionType;

    OPCODE opcode;
    OPCODE_DATATYPE opcodeDatatype;

    int reg0;
    int reg1;

    union ARG3 {
        char *label;
        float floatImmediate;
        int intImmediate;
        int reg2;
    } ARG3;

} Instruction;
typedef union Registers {

    int intValue;
    float floatValue;

} Registers;


struct VM {

    size_t programCounter;             //Program counter index into instructionMemory

    Registers *registers;              //Pointer to register array (NOTE - SP is considered to be to R0)

    Instruction *instructionMemory;    //Array of instructions
    RAM_TYPE *RAM;                      //Bytes

};




VM VirtualMachine; //Only ONE should exist
//Dictionary for labels
char **labelKey = NULL;
size_t *labelValue = NULL;
size_t labelDictionarySize = 0;
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
    (VirtualMachine.registers[0]).intValue = sizeOfRam - 1; //Set the SP to the last element in RAM (stack grows backwards)


    return true;
}


bool destroy_VM(void) {
    //Free memory associated with VM
    if(VirtualMachine.registers != NULL) {
        free(VirtualMachine.registers);
        VirtualMachine.registers = NULL;
    }
    if(VirtualMachine.RAM != NULL) {
        free(VirtualMachine.RAM);
        VirtualMachine.RAM = NULL;
    }
    if(VirtualMachine.instructionMemory != NULL) {

        for(int i = 0; current_instruction.opcode != END; i++) {
            if(current_instruction.instructionType == I || current_instruction.instructionType == J) {
                if(current_instruction.ARG3.label != NULL) {
                    free(current_instruction.ARG3.label);
                    current_instruction.ARG3.label = NULL;
                }
            }
        }
    }
    return true;
}























void print_dictionary(void) {

    printf("       Key   |||        Value\n");
    printf("---------------------------------\n");
    for(int i = 0; i < labelDictionarySize; i++) {
        printf("%10s   |||   %10zu\n",labelKey[i], labelValue[i]);        
    }
    return;
}
void print_instruction(Instruction instruction) {

    printf("Instruction Type: %d\n",instruction.instructionType);
    printf("Opcode: %d\n",instruction.opcode);
    printf("Opcode datatype: %d\n",instruction.opcodeDatatype);
    printf("Source register: %d\n",instruction.reg0);
    printf("Argument register: %d\n",instruction.reg1);


    if(instruction.instructionType == R) {
        printf("Argument register: %d\n",instruction.ARG3.reg2);
    } else if(instruction.instructionType == I) {
        if(instruction.opcodeDatatype == FLOAT) {
            printf("Immediate: %f\n",instruction.ARG3.floatImmediate);
        } else {
            printf("Immediate: %d\n",instruction.ARG3.intImmediate);
        }
    } else if(instruction.instructionType == C || instruction.instructionType == L || instruction.instructionType == J) {

        if(instruction.ARG3.label != NULL) {
            printf("Label: %s\n",instruction.ARG3.label);
        }
    }

    printf("\n\n");
    return;
}

bool is_integer(char *str) {

    for(int i = 0; str[i] != '\0'; i++) {
        if(isdigit(str[i]) == 0) {
            return false;
        }
    }
    return true;
}
bool is_float_or_integer(char *str) {

    bool foundDecimal = false;
    for(int i = 0; str[i] != '\0'; i++) {

        if(str[i] =='.' && foundDecimal == false) {
            foundDecimal = true;
        } else if(isdigit(str[i]) == 0) {
            return false;
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
    char copyInstructionInputBuffer[INSTRUCTION_INPUT_BUFFER]; //Used for displaying errors since strtok is destructuve

    //Note: programCounter being used TEMPORARILY to keep track of the instructionMemory size
    VirtualMachine.programCounter = 0;
    char *currentToken = NULL;
    for(int i = 0; fgets(instructionInputBuffer, array_len(instructionInputBuffer), IRfile); i++) {


        strcpy(copyInstructionInputBuffer, instructionInputBuffer);
        if(i == VirtualMachine.programCounter) { //Reallocate memory
            VirtualMachine.instructionMemory = realloc(VirtualMachine.instructionMemory, (VirtualMachine.programCounter + INSTRUCTION_MEMORY_EXPANSION) * sizeof(Instruction)); //NEED TO HANDLE IF REALLOC FAILS (DO LATER)
            if(VirtualMachine.instructionMemory == NULL) {
                printf("Memory allocation failure when expanding instruction memory\n");
                return false;
            }
            VirtualMachine.programCounter += INSTRUCTION_MEMORY_EXPANSION;
        }

        //Get instruction type
        currentToken = strtok(instructionInputBuffer, " \n");
        if(currentToken == NULL) { //Empty line
            i--;
            continue;
        }
        



        if(strcmp(currentToken, "[R]") == 0) {
            current_instruction.instructionType = R; //Register


            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected opcode: '%s'\n",copyInstructionInputBuffer);
                return false;
            }
            if(strcmp(currentToken, "ADD_I") == 0) {
                current_instruction.opcode = ADD_I;
                current_instruction.opcodeDatatype = INTEGER;
            } else if(strcmp(currentToken, "ADD_F") == 0) {
                current_instruction.opcode = ADD_F;
                current_instruction.opcodeDatatype = FLOAT;
            } else if(strcmp(currentToken, "SUB_I") == 0) {
                current_instruction.opcode = SUB_I;
                current_instruction.opcodeDatatype = INTEGER;
            } else if(strcmp(currentToken, "SUB_F") == 0) {
                current_instruction.opcode = SUB_F;
                current_instruction.opcodeDatatype = FLOAT;
            } else if(strcmp(currentToken, "MUL_I") == 0) {
                current_instruction.opcode = MUL_I;
                current_instruction.opcodeDatatype = INTEGER;
            } else if(strcmp(currentToken, "MUL_F") == 0) {
                current_instruction.opcode = MUL_F;
                current_instruction.opcodeDatatype = FLOAT;
            } else if(strcmp(currentToken, "DIV_I") == 0) {
                current_instruction.opcode = DIV_I;
                current_instruction.opcodeDatatype = INTEGER;
            } else if(strcmp(currentToken, "DIV_F") == 0) {
                current_instruction.opcode = DIV_F;
                current_instruction.opcodeDatatype = FLOAT;
            } else {
                printf("Unrecognised R type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }

            //Register arguments

            //Destination register
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected destination register in R type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            if(currentToken[0] != 'R' || is_integer(currentToken + 1) == false) { //Skip the fist letter (which should be 'R')
                printf("Incorrectly formatted register destination argument: '%s'\n",copyInstructionInputBuffer);
                return false;
            }

            current_instruction.reg0 = atoi(currentToken + 1); //Skip the first "R"



            //Source register 1
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected source register in R type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            if(currentToken[0] != 'R' || is_integer(currentToken + 1) == false) { //Skip the fist letter (which should be 'R')
                printf("Incorrectly formatted register source argument: '%s'\n",copyInstructionInputBuffer);
                return false;
            }
            current_instruction.reg1 = atoi(currentToken + 1); //Skip the first "R"



            //Source register 2
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected source register in R type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            if(currentToken[0] != 'R' || is_integer(currentToken + 1) == false) { //Skip the fist letter (which should be 'R')
                printf("Incorrectly formatted register source argument: '%s'\n",copyInstructionInputBuffer);
                return false;
            }
            current_instruction.ARG3.reg2 = atoi(currentToken + 1); //Skip the first "R"


            if(strtok(NULL, " \n") != NULL) {
                printf("Too many operands passed to R type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }

        } else if(strcmp(currentToken, "[I]") == 0) {
            current_instruction.instructionType = I; //Immediate

            bool isFloat = false;
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected opcode: '%s'\n",copyInstructionInputBuffer);
                return false;
            }
            if(strcmp(currentToken, "ADD_I") == 0) {
                current_instruction.opcode = ADD_I;
                current_instruction.opcodeDatatype = INTEGER;
            } else if(strcmp(currentToken, "ADD_F") == 0) {
                current_instruction.opcode = ADD_F;
                current_instruction.opcodeDatatype = FLOAT;
                isFloat = true;


            } else if(strcmp(currentToken, "SUB_I") == 0) {
                current_instruction.opcode = SUB_I;
                current_instruction.opcodeDatatype = INTEGER;
            } else if(strcmp(currentToken, "SUB_F") == 0) {
                current_instruction.opcode = SUB_F;
                current_instruction.opcodeDatatype = FLOAT;
                isFloat = true;


            } else if(strcmp(currentToken, "MUL_I") == 0) {
                current_instruction.opcode = MUL_I;
                current_instruction.opcodeDatatype = INTEGER;
            } else if(strcmp(currentToken, "MUL_F") == 0) {
                current_instruction.opcode = MUL_F;
                current_instruction.opcodeDatatype = FLOAT;
                isFloat = true;


            } else if(strcmp(currentToken, "DIV_I") == 0) {
                current_instruction.opcode = DIV_I;
                current_instruction.opcodeDatatype = INTEGER;
            } else if(strcmp(currentToken, "DIV_F") == 0) {
                current_instruction.opcode = DIV_F;
                current_instruction.opcodeDatatype = FLOAT;
                isFloat = true;

            } else {
                printf("Unrecognised I type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }

            //Register arguments

            //Destination register
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected destination register in I type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            if(currentToken[0] != 'R' || is_integer(currentToken + 1) == false) { //Skip the fist letter (which should be 'R')
                printf("Incorrectly formatted register destination argument: '%s'\n",copyInstructionInputBuffer);
                return false;
            }

            current_instruction.reg0 = atoi(currentToken + 1); //Skip the first "R"



            //Source register 1
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected source register in I type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            if(currentToken[0] != 'R' || is_integer(currentToken + 1) == false) { //Skip the fist letter (which should be 'R')
                printf("Incorrectly formatted register source argument: '%s'\n",copyInstructionInputBuffer);
                return false;
            }
            current_instruction.reg1 = atoi(currentToken + 1); //Skip the first "R"



            //Immediate
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected immediate in I type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            if(is_float_or_integer(currentToken) == false) {
                printf("Incorrectly formatted immediate argument: '%s'\n",copyInstructionInputBuffer);
                return false;
            }

            if(isFloat == false) {
                current_instruction.ARG3.intImmediate = atoi(currentToken);
            } else {
                current_instruction.ARG3.floatImmediate = atof(currentToken);
            }


            if(strtok(NULL, " \n") != NULL) {
                printf("Too many operands passed to I type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }


        } else if(strcmp(currentToken, "[C]") == 0) {
            current_instruction.instructionType = C; //Compare


            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected opcode: '%s'\n",copyInstructionInputBuffer);
                return false;
            }
            if(strcmp(currentToken, "BEQ") == 0) {
                current_instruction.opcode = BEQ;
                current_instruction.opcodeDatatype = NONE;
            } else if(strcmp(currentToken, "BLT") == 0) {
                current_instruction.opcode = BLT;
                current_instruction.opcodeDatatype = NONE;
            } else if(strcmp(currentToken, "BLE") == 0) {
                current_instruction.opcode = BLE;
                current_instruction.opcodeDatatype = NONE;
            } else {
                printf("Unrecognised C type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }

            //Register arguments

            //Destination register
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected destination register in C type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            if(currentToken[0] != 'R' || is_integer(currentToken + 1) == false) { //Skip the fist letter (which should be 'R')
                printf("Incorrectly formatted register destination argument: '%s'\n",copyInstructionInputBuffer);
                return false;
            }

            current_instruction.reg0 = atoi(currentToken + 1); //Skip the first "R"



            //Source register 1
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected source register in C type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            if(currentToken[0] != 'R' || is_integer(currentToken + 1) == false) { //Skip the fist letter (which should be 'R')
                printf("Incorrectly formatted register source argument: '%s'\n",copyInstructionInputBuffer);    
                return false;
            }
            current_instruction.reg1 = atoi(currentToken + 1); //Skip the first "R"



            //Label
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected label in C type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            current_instruction.ARG3.label = malloc((strlen(currentToken) + 1) * sizeof(char));
            if(current_instruction.ARG3.label == NULL) {
                printf("Failure to allocate memory for label\n");
                return false;
            }
            strcpy(current_instruction.ARG3.label, currentToken);



            if(strtok(NULL, " \n") != NULL) {
                printf("Too many operands passed to C type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }





        } else if(strcmp(currentToken, "[J]") == 0) {
            current_instruction.instructionType = J; //Jump

            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected opcode: '%s'\n",copyInstructionInputBuffer);
                return false;
            }
            if(strcmp(currentToken, "JUM") == 0) {
                current_instruction.opcode = JUM;
                current_instruction.opcodeDatatype = NONE;
            } else if(strcmp(currentToken, "JAL") == 0) {
                current_instruction.opcode = JAL;
                current_instruction.opcodeDatatype = NONE;
            } else {
                printf("Unrecognised C type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }


            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected label in C type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            current_instruction.ARG3.label = malloc((strlen(currentToken) + 1) * sizeof(char));
            if(current_instruction.ARG3.label == NULL) {
                printf("Failure to allocate memory for label\n");
                return false;
            }
            strcpy(current_instruction.ARG3.label, currentToken);




            if(strtok(NULL, " \n") != NULL) {
                printf("Too many operands passed to J type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }


        } else if(strcmp(currentToken, "[L]") == 0) {
            current_instruction.instructionType = L; //Label

            //Put into a dictionary



            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected opcode: '%s'\n",copyInstructionInputBuffer);
                return false;
            }
            if(strcmp(currentToken, "LABEL") == 0) {

            } else {
                printf("Unrecognised L type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }




            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected label: '%s'\n",copyInstructionInputBuffer);
                return false;
            }


            labelKey = realloc(labelKey, ((labelDictionarySize + 1) * sizeof(char*)));
            labelValue = realloc(labelValue, ((labelDictionarySize + 1) * sizeof(size_t)));   

            if(labelKey == NULL || labelValue == NULL) {
                printf("Failed to allocate memory for label dictionary\n");
                return false;
            }
            labelKey[labelDictionarySize] = malloc((strlen(currentToken) + 1) * sizeof(char));


            if(labelKey[labelDictionarySize] == NULL) {
                printf("Failed to allocate memory for label dictionary\n");
                return false;
            }




            strcpy(labelKey[labelDictionarySize], currentToken);
            labelValue[labelDictionarySize] = i; //Assign to current insruction address

            labelDictionarySize += 1; 

            //printf("key: %s || value: %d\n",labelKey[labelDictionarySize], labelValue[labelDictionarySize]);

            if(strtok(NULL, " \n") != NULL) {
                printf("Too many operands passed to L type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }

            i--; //Do this because this instruction should not appear in memory

        } else if(strcmp(currentToken, "[A]") == 0) {
            current_instruction.instructionType = A; //Abstract




            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected opcode: '%s'\n",copyInstructionInputBuffer);
                return false;
            }
            if(strcmp(currentToken, "ALLOC") == 0) {
                current_instruction.opcode = ALLOC;
                current_instruction.opcodeDatatype = NONE;
            } else if(strcmp(currentToken, "FREE") == 0) {
                current_instruction.opcode = FREE;
                current_instruction.opcodeDatatype = NONE;
            } else {
                printf("Unrecognised A type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }




            //Destination register
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected destination register in A type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            if(currentToken[0] != 'R' || is_integer(currentToken + 1) == false) { //Skip the fist letter (which should be 'R')
                printf("Incorrectly formatted register destination argument: '%s'\n",copyInstructionInputBuffer);
                return false;
            }

            current_instruction.reg0 = atoi(currentToken + 1); //Skip the first "R"



            //Source register 1
            currentToken = strtok(NULL, " \n");
            if(currentToken == NULL) {
                printf("Expected source register in A type instruciton: '%s'\n", copyInstructionInputBuffer);
                return false;
            }
            if(currentToken[0] != 'R' || is_integer(currentToken + 1) == false) { //Skip the fist letter (which should be 'R')
                printf("Incorrectly formatted register source argument: '%s'\n",copyInstructionInputBuffer);    
                return false;
            }
            current_instruction.reg1 = atoi(currentToken + 1); //Skip the first "R"






            if(strtok(NULL, " \n") != NULL) {
                printf("Too many operands passed to A type instruction: '%s'\n",copyInstructionInputBuffer);
                return false;
            }



        } else { //Unrecognised instruction type
            printf("Unrecognised instruction '%s'\n",copyInstructionInputBuffer);
            return false;
        }
        //print_instruction(current_instruction);
    }
    


    //Cleanup
    fclose(IRfile);
    VirtualMachine.programCounter = 0;
    //print_dictionary();
    return true;
}

































































































































