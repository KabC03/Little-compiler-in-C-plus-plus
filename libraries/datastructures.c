#include "datastructures.h"



//Macro for initialisation
#define initialise(datatype, dataSize)\
    do {\
        if(datatype == NULL || dataSize == 0) {\
            return false;\
        } else {\
            (datatype)->head = NULL;\
            (datatype)->datatypeSize = dataSize;\
        }\
        return true;\
    } while(0)










struct Node {

    uint8_t *data;
    struct Node *next;
};
struct PriorityNode {

    uint8_t *data;
    struct PriorityNode *next;
};


//Stack
/**
 * stack_initialise
 * ===============================================
 * Brief: Initialise a stack before use
 * 
 * Param: *stack - stack of interest
 *        dataSize - size of the datatype to be stored in the stack
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool stack_initialise(Stack *const stack, size_t dataSize) {

    initialise(stack, dataSize);
}




/**
 * stack_push
 * ===============================================
 * Brief: Push an item onto the stack
 * 
 * Param: *stack - stack of interest
 *        *data - data to be pushed onto the stack
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool stack_push(Stack *const stack, void *data) {

    if(stack == NULL || data == NULL) {
        return false;
    } else {

        Node *newNode = malloc(sizeof(Node));
        if(newNode == NULL) {
            return false;
        }
        newNode->data = malloc(sizeof(uint8_t) * stack->datatypeSize);
        if(newNode->data == NULL) {
            free(newNode);
            return false;
        }
        memcpy(newNode->data, data, stack->datatypeSize);


        newNode->next = stack->head;
        stack->head = newNode;
    }

    return true;
}




/**
 * stack_peak
 * ===============================================
 * Brief: Peak an item from the stack
 * 
 * Param: *stack - stack of interest
 *        *result - output pointer of where the result should be stored
 * Return: void* - pointer to result
 * 
 */
const void* stack_peak(Stack *const stack) {

    if(stack == NULL) {
        return NULL;
    } else {

        if(stack->head == NULL) {
            return NULL;
        } else {
            return stack->head->data;
        }
    }

    return NULL;
}






/**
 * stack_pop
 * ===============================================
 * Brief: Pop an item onto the stack
 * 
 * Param: *stack - stack of interest
 *        *result - output pointer of where the result should be stored
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool stack_pop(Stack *const stack, void *result) {

    if(stack == NULL || result == NULL) {
        return false;
    } else {

        if(stack->head == NULL) {
            result = NULL;
            return false;


        } else {
            memcpy(result, stack->head->data, stack->datatypeSize);

            Node *freePtr = stack->head;
            free(stack->head->data);



            stack->head = stack->head->next;
            free(freePtr);
        }

    }

    return true;
}














































































