#include "register.h"



/**
 * register_print
 * ===============================================
 * Brief: Print an array of registers
 * 
 * Param: *registerStates - Vector of register states
 * 
 * Return: RETURN_CODE - Indicating succes or type of failure 
 * 
 */
RETURN_CODE register_print(Vector *registerStates) {

    printf("\n\n\n");
    if(registerStates == NULL) {
        printf("WARNING in 'register_print' - registerStates is unexpectedly NULL\n");

    } else {
        VariableData *currentRegister = NULL;
        for(size_t i = 1; i < vector_get_length(registerStates) + 1; i++) {
            currentRegister = (VariableData*)vector_get_index(registerStates, i);
            if(currentRegister == NULL) {
                printf("WARNING in 'register_swap' - currentRegister is unexpectedly NULL\n");
            }
            const char *currentVarName = dynamic_string_read(&(currentRegister->name));
            if(currentVarName == NULL) {
                printf("WARNING in 'register_swap' - currentVarName is unexpectedly NULL\n");
            }
            printf("Name: %s - register: %zu, %zu\n", currentVarName, currentRegister->registerNumber, i);
        }

    }
    printf("\n\n\n");
    return _SUCCESS_;
}



/**
 * register_load_to_register
 * ===============================================
 * Brief: Load a variable OR immediate into a register and save whats pushed out
 * 
 * Param: *registerStates - Vector of register states
 *        *newVariable - Variable of interest (NOTE: If NULL this means an immediate will be taken)
 *        blacklistedIndex - Index that should not be overwritten
 *        immediate - Integer immediate
 * 
 * Return: RETURN_CODE - Indicating succes or type of failure 
 * 
 */
size_t register_load_to_register(Vector *registerStates, VariableData *newVariable, size_t blacklistedIndex, int immediate, FILE *irFilePtr) {

    size_t index = -1;
    if(registerStates == NULL || irFilePtr == NULL) {
        printf("WARNING in 'register_swap' - registerStates or irFilePtr is unexpectedly NULL\n");
        return -1;

    } else {

        //Search for unused register
        for(size_t i = 0; i < vector_get_length(registerStates) + 1; i++) {
            VariableData *currentRegister = (VariableData*)vector_get_index(registerStates, i);
            if(currentRegister == NULL) {
                return _INTERNAL_ERROR_;
            }
            if(i == blacklistedIndex) {
                continue;
            }

            if(currentRegister->inUse == false) {

                if(newVariable != NULL) {
                    currentRegister->baseOffset = newVariable->baseOffset;
                    currentRegister->inUse = true;
                    currentRegister->registerNumber = newVariable->registerNumber;
                    currentRegister->name = newVariable->name;
                    currentRegister->timesRequested = newVariable->timesRequested;
                } else {
                    currentRegister->inUse = false;
                }
                return i;
            }
        }






    }

    return index;
}


















