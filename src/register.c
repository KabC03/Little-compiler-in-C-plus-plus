#include "register.h"

/**
 * register_load_to_register
 * ===============================================
 * Brief: Load a variable OR immediate into a register and save whats pushed out
 * 
 * Param: *registerStates - Vector of register states
 *        *newVariable - Variable of interest (NOTE: If NULL this means an immediate will be taken)
 *        immediate - Integer immediate
 * 
 * Return: RETURN_CODE - Indicating succes or type of failure 
 * 
 */
size_t register_load_to_register(Vector *registerStates, VariableData *newVariable, int immediate, FILE *irFilePtr) {

    size_t index = -1;
    if(registerStates == NULL || irFilePtr == NULL) {
        printf("WARNING in 'register_swap' - registerStates or irFilePtr is unexpectedly NULL\n");
        return -1;

    } else {

        VariableData *currentRegister = NULL;
        VariableData *leastUsedRegister = NULL;
        bool skipFor = false;

        leastUsedRegister = (VariableData*)vector_get_index(registerStates, 0);
        if(leastUsedRegister == NULL) {
            printf("WARNING in 'register_swap' - leastUsedRegister is unexpectedly NULL\n");
        }
        if(leastUsedRegister->inUse == false) {
            index = 0;
            skipFor = true; //Dont need to run for loop
        }

        for(size_t i = 1; i < vector_get_length(registerStates) + 1 && skipFor == false; i++) {
            currentRegister = (VariableData*)vector_get_index(registerStates, i);
            if(currentRegister == NULL) {
                printf("WARNING in 'register_swap' - currentRegister is unexpectedly NULL\n");
            }

            if(currentRegister->inUse == false) { //If register isnt used can store variable here
                leastUsedRegister = currentRegister;
                index = i;
                break;
            }
            if(currentRegister->timesRequested < leastUsedRegister->timesRequested) {
                leastUsedRegister = currentRegister;
            }
        }


        //Save the old variable if its being used
        if(leastUsedRegister->inUse == true) {
            internal_macro_save(leastUsedRegister->registerNumber, leastUsedRegister->baseOffset, irFilePtr);
        }


        if(newVariable == NULL) { //Save an immediate to the register

            leastUsedRegister->inUse = false; //Mark it as unused so compiler knows no variable is stored here
            internal_macro_load_immediate(index, immediate, irFilePtr);
        } else {

            //Write the new variable in
            newVariable->registerNumber = index;
            newVariable->timesRequested++;
            newVariable->inUse = true;
            if(vector_set_index(registerStates, index, newVariable) == false) {
                printf("ERROR in 'register_swap' - Failed to set new variable\n");
                exit(1);
            }
            internal_macro_load(index, newVariable->baseOffset, irFilePtr);
        }

    }

    return index;
}


















