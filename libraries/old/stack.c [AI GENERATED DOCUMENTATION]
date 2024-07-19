#include "stack.h"




/*
 * Internal Structure Definition
 * -----------------------------
 * The StackNode structure is defined here to ensure it is not visible outside this implementation file.
 */
struct StackNode {
    void *data;
    struct StackNode *nextPtr;
};


/*
 * Function: stack_initialise
 * --------------------------
 * Initializes a stack to an empty state.
 *
 * Parameters:
 *   stack - Pointer to the stack to be initialized.
 *
 * Note:
 *   This function should be called before any other operations on the stack.
 */
void stack_initialise(Stack *stack) {
    (*stack).head = NULL;
    return;
}




/*
 * Function: push_generic
 * ----------------------
 * (Internal Use Only) Pushes a new data element onto the stack. This function allocates a new StackNode and a buffer
 * for data, copies the given data into the new buffer, and links the new node into the stack.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 *   data - Pointer to the data to be pushed onto the stack.
 *   dataSize - Size of the data to be pushed.
 *
 * Returns:
 *   true if the data was successfully pushed, false if memory allocation failed.
 *
 * Note:
 *   Users should never call this function directly. Instead, use stack_push_size_t or stack_push_Token.
 */
bool push_generic(Stack *stack, void *data, size_t dataSize) {

    if(stack == NULL || data == NULL) return false;

    StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));
    if(newNode == NULL) return false;


    newNode->data = (void*)malloc(dataSize);
    if(newNode->data == NULL) {
        free(newNode);
        return false;
    }

    memcpy(newNode->data, data, dataSize);


    newNode->nextPtr = stack->head;
    stack->head = newNode;

    return true;
}


/*
 * Function: pop_generic
 * ---------------------
 * (Internal Use Only) Pops the top data element from the stack. This function removes the top stack node, retrieves
 * its data, and frees the node. The caller is responsible for freeing the returned data.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 *
 * Returns:
 *   Pointer to the data of the popped element, or NULL if the stack is empty.
 *
 * Note:
 *   Users should never call this function directly. Instead, use stack_pop_size_t or stack_pop_Token.
 */
void* pop_generic(Stack *stack) {

    void *result = NULL;
    if(stack == NULL) return NULL; //Temporary

    if(stack->head == NULL) {

    } else {
        result = stack->head->data;
        if(result == NULL) return NULL; //Something went wrong - return -1 for now
        
        StackNode *freeNode = stack->head;
        stack->head = stack->head->nextPtr;
        free(freeNode);
    }

    return result; //User must free this pointer
}


/*
 * Function: destroy_generic
 * -------------------------
 * (Internal Use Only) Destroys a stack, freeing all of its elements and the data they contain.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 *
 * Returns:
 *   true if the stack was successfully destroyed, false otherwise (e.g., if the stack was NULL).
 *
 * Note:
 *   Users should never call this function directly. Instead, use stack_destroy_size_t or stack_destroy_Token.
 */
bool destroy_generic(Stack *stack) {

    if(stack == NULL) return false; //Should NEVER happen

    if(stack->head == NULL) {

    } else {

        while(stack->head != NULL) {
            void *data = stack->head->data;
            StackNode *freeNode = stack->head;
            stack->head = stack->head->nextPtr;
            free(freeNode);

            if(data != NULL) free(data); //Data should NEVER be NULL - but checking just incase

        }
    }

    return true;
}




/*
 * Function: stack_print_size_t
 * ----------------------------
 * Prints the contents of the stack for debugging purposes, displaying size_t values.
 *
 * Parameters:
 *   stack - Pointer to the stack to be printed.
 */
void stack_print_size_t(Stack *stack) {

    void *resultPtr = NULL;
    size_t result = 0;
    printf(" ┌───────┐\n");
    while(1) {
        resultPtr = pop_generic(stack);
        if(resultPtr == NULL) break;

        result = *((size_t*)(resultPtr));
        free(resultPtr);
        printf(" │  %2zu   │\n", result);
        printf(" ├───────┤\n");
    }
    printf(" └───────┘\n");

    return;
}


/*
 * Function: stack_push_size_t
 * ---------------------------
 * Pushes a size_t value onto the stack.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 *   data - size_t value to push.
 *
 * Returns:
 *   true if the value was successfully pushed, false otherwise.
 */
bool stack_push_size_t(Stack *stack, size_t data) {

    if(push_generic(stack, &data, sizeof(data)) == false) return false;

    return true;
}







/*
 * Function: stack_pop_size_t
 * --------------------------
 * Pops a size_t value from the stack.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 *
 * Returns:
 *   size_t value popped from the stack; returns (size_t)-1 if the stack is empty.
 */
size_t stack_pop_size_t(Stack *stack) {

    void *resultPtr = pop_generic(stack);
    if(resultPtr == NULL) return -1; //Temporary
    size_t result = *((size_t*)(resultPtr));
    free(resultPtr);

    return result;  
}



/*
 * Function: stack_peak_size_t
 * --------------------------
 * Peak a size_t value from the stack.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 *
 * Returns:
 *   size_t value peaked from the stack; returns (size_t)-1 if the stack is empty.
 */
size_t stack_peak_size_t(Stack *stack) {

    size_t returnVal = stack_pop_size_t(stack); //Returns -1 on failure already

    if(stack_push_size_t(stack, returnVal) == false) return -1; //Temporary


    return returnVal;  
}








/*
 * Function: stack_destroy_size_t
 * ------------------------------
 * Destroys a stack that contains size_t values, freeing all nodes and their data.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 */
void stack_destroy_size_t(Stack *stack) {

    destroy_generic(stack);
}








//Tokens


/*
 * Function: stack_print_size_t
 * ----------------------------
 * Prints the contents of the stack for debugging purposes, displaying size_t values.
 *
 * Parameters:
 *   stack - Pointer to the stack to be printed.
 */
void stack_print_Token(Stack *stack) {

    void *resultPtr = NULL;
    Token result;

    printf(" ┌───────┐\n");
    while(1) {
        resultPtr = pop_generic(stack);
        if(resultPtr == NULL) break;

        result = *((Token*)(resultPtr));
        free(resultPtr);
        printf(" │  %2d   │\n", result.tokenType);
        printf(" ├───────┤\n");
    }
    printf(" └───────┘\n");

    return;
}



/*
 * Function: stack_push_Token
 * --------------------------
 * Pushes a Token onto the stack.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 *   data - Token to push.
 *
 * Returns:
 *   true if the Token was successfully pushed, false otherwise.
 */
bool stack_push_Token(Stack *stack, Token data) {

    if(push_generic(stack, &data, sizeof(data)) == false) return false;

    return true;
}



/*
 * Function: stack_pop_Token
 * -------------------------
 * Pops a Token from the stack.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 *
 * Returns:
 *   Token popped from the stack; returns a Token with type TOK_INVALID if the stack is empty.
 */
Token stack_pop_Token(Stack *stack) {

    Token result;
    result.tokenType = TOK_END_ARRAY;



    void *resultPtr = pop_generic(stack);
    if(resultPtr == NULL) return result; //Return end of array token



    result = *((Token*)(resultPtr));
    free(resultPtr);



    return result;  
}



/*
 * Function: stack_peak_Token
 * --------------------------
 * Peak a Token value from the stack.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 *
 * Returns:
 *   Token value peaked from the stack; returns (Token)-1 if the stack is empty.
 */
Token stack_peak_Token(Stack *stack) {

    Token returnVal = stack_pop_Token(stack); //Returns -1 on failure already

    returnVal.tokenType = TOK_END_ARRAY;
    if(stack_push_Token(stack, returnVal) == false) return returnVal;


    return returnVal;  
}






/*
 * Function: stack_destroy_Token
 * -----------------------------
 * Destroys a stack that contains Tokens, freeing all nodes and their data.
 *
 * Parameters:
 *   stack - Pointer to the stack.
 */
void stack_destroy_Token(Stack *stack) {

    destroy_generic(stack);
}


