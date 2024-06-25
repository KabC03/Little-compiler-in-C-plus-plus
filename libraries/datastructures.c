#include "datastructures.h"



//Macros
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


#define size(datatype)\







struct ListNode {

    uint8_t *data;
    struct ListNode *next;
    struct ListNode *back;
};
struct Node {

    uint8_t *data;
    struct Node *next;
};
struct PriorityNode {

    uint8_t *data;
    struct PriorityNode *next;
    struct Node *back;
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
 * stack_size
 * ===============================================
 * Brief: Size of a stack
 * 
 * Param: *stack - stack of interest
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
size_t stack_length(Stack *const stack) {

    size_t size = 0;
    if(stack == NULL) { 
        return 0;
    } else {
        Node *currentNode = stack->head;
        while(currentNode != NULL) {
            size++;
            currentNode = currentNode->next;
        }
    }
    return size;
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





//Queue


/*
TODO:
- Initialise
- Length
- Enqueue (with priority)
- Dequeue

- Destroy queue
*/


//Priority Queue


/*
TODO:
- Initialise
- Length
- Enqueue (with priority)
- Dequeue

- Destroy queue
*/


//Linked list




/**
 * LL_print
 * ===============================================
 * Brief: Print a LL
 * 
 * Param: *linkedList - linkedList of interest
 * 
 * Return: bool - T/F depending on if list exists
 * 
 */
bool LL_print(LinkedList *const linkedList) {

    if(linkedList == NULL) {
        return false;
    } else {

        ListNode *currentNode = linkedList->head;

        while(currentNode != NULL) {

            printf("%d, ",*(int*)(currentNode->data));
            currentNode = currentNode->next;
        }


    }

    return true;
}






/**
 * LL_initialise
 * ===============================================
 * Brief: Initialise a LL before use
 * 
 * Param: *linkedList - linkedList of interest
 *        dataSize - size of the datatype to be stored in the linkedList
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool LL_initialise(LinkedList *const linkedList, size_t dataSize) {

    if(linkedList == NULL || dataSize == 0) {
        return false;
    } else {
        linkedList->head = NULL;
        linkedList->end = NULL;
        linkedList->datatypeSize = dataSize;
    }
    return true;
}


/**
 * LL_size
 * ===============================================
 * Brief: Size of a LL (number of elements)
 * 
 * Param: *linkedList - linkedList of interest
 * 
 * Return: size_t - Size of list
 * 
 */
size_t LL_length(LinkedList *const linkedList) {

    size_t size = 0;
    if(linkedList == NULL) { 
        return 0;
    } else {
        ListNode *currentNode = linkedList->head;
        while(currentNode != NULL) {
            size++;
            currentNode = currentNode->next;
        }
    }
    return size;
}





/**
 * LL_push_front
 * ===============================================
 * Brief: Insert at beggining of list
 * 
 * Param: *linkedList - linkedList of interest
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool LL_insert_front(LinkedList *const list, void *data) {

    if(list == NULL || data == NULL) {
        return false;
    } else {

        ListNode *newNode = malloc(sizeof(ListNode));
        if(newNode == NULL) {
            return false;
        }
        newNode->data = malloc(sizeof(uint8_t) * list->datatypeSize);
        if(newNode->data == NULL) {
            free(newNode);
            return false;
        }
        memcpy(newNode->data, data, list->datatypeSize);

        if(list->head == NULL) {
            list->end = newNode;
        }


        newNode->next = list->head;
        newNode->back = NULL;
        list->head = newNode;
    }

    return true;
}



/**
 * LL_delete_front
 * ===============================================
 * Brief: Delete at beggining of list
 * 
 * Param: *linkedList - linkedList of interest
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool LL_delete_front(LinkedList *const list) {

    if(list == NULL) {
        return false;
    } else {

        if(list->head == NULL) {
            return false;


        } else {

            ListNode *freePtr = list->head;
            free(list->head->data);



            list->head = list->head->next;

            if(list->head == NULL) {
                list->end = NULL;
            }

            list->head->back = NULL;
            free(freePtr);
        }

    }

    return true;
}


/**
 * LL_insert_back - WARNING DOES NOT WORK
 * ===============================================
 * Brief: Insert at back of list
 * 
 * Param: *linkedList - linkedList of interest
 *        *data - data to be added
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool LL_insert_back(LinkedList *const list, void *data) {

    if(list == NULL) {
        return false;
    } else {



        ListNode *newNode = malloc(sizeof(ListNode));
        if(newNode == NULL) {
            return false;
        }

        newNode->data = malloc(sizeof(uint8_t) * list->datatypeSize);
        if(newNode->data == NULL) {
            free(newNode);
            return false;
        }
        memcpy(newNode->data, data, list->datatypeSize);


        if(list->end == NULL) {

            list->end = newNode;
            list->head = newNode;
        } else {

            list->end->next = newNode;
        }

        newNode->next = NULL;
        newNode->back = list->end;
    }


    return true;
}





/**
 * LL_delete_back
 * ===============================================
 * Brief: Delete at back of list
 * 
 * Param: *linkedList - linkedList of interest
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool LL_delete_back(LinkedList *const list) {

    if(list == NULL) {
        return false;
    } else {

        if(list->end == NULL) {
            return false;
        }

        ListNode *freeNode = list->end;
        ListNode *currentNode = list->end->back;

        if(currentNode != NULL) {
            currentNode->next = NULL;
            list->end = currentNode;

        } else {

            list->end = NULL;
            list->head = NULL;

        }





        free(freeNode->data);

        free(freeNode);
    }


    return true;
}










/*
TODO:

- Insert at index
- Delete at index

- Get item at index

- Delete a linked list
- Copy a linked list
*/





//Simple linked list
/*

TODO
- Mainly meant to be embedded in other libraries (e.g map)
- Must pass the head NODE not a LL
- Singly linked list

- Insert at front
- Delete by key
- Search for key

*/


//Initialise
bool map_LL_initialise(MapList *const list, size_t inputKeySize, size_t inputValueSize) {

    if(list == NULL || inputKeySize == 0 || inputValueSize == 0) {
        return false;
    } else {

        list->keySize = inputKeySize;
        list->keySize = inputValueSize;
    
        list->firstNode.key = NULL;
        list->firstNode.value = NULL;
        list->firstNode.next = NULL;

    }


    return true;
}


//Insert after first node at the front
bool map_LL_insert_front(MapList *const list, void *inputKey, void *inputValue) {

    if(list == NULL || inputKey == NULL || inputValue == NULL) {
        return false;
    } else {

        if(list->firstNode.next == NULL) { //Insert at this node

            list->firstNode.key = malloc(sizeof(list->keySize));
            if(list->firstNode.key == NULL) {
                return false;
            }
            list->firstNode.value = malloc(sizeof(list->valueSize));
            if(list->firstNode.value == NULL) {
                free(list->firstNode.key);
                return false;
            }

            memcpy(list->firstNode.key, inputKey, list->keySize);
            memcpy(list->firstNode.value, inputValue, list->valueSize);

        } else { //Insert after first node
            
            MapListNode *newNode = malloc(sizeof(MapListNode));
            newNode->next = list->firstNode.next;

            newNode->key = malloc(sizeof(list->keySize));
            if(list->firstNode.key == NULL) {
                free(newNode);
                return false;
            }
            list->firstNode.value = malloc(sizeof(list->valueSize));
            if(list->firstNode.value == NULL) {
                free(newNode->key);
                free(newNode);
                return false;
            }


            memcpy(newNode->key, inputKey, list->keySize);
            memcpy(newNode->value, inputValue, list->valueSize);

            list->firstNode.next = newNode;
        }
    }


    return true;
}




//Delete by a key
bool map_LL_delete_key(MapList *const list, void *inputKey) {

    if(list == NULL || inputKey == NULL) {
        return false;
    } else {

        if(memcmp(list->firstNode.key, inputKey, list->keySize) == 0) {

            if(list->firstNode.next == NULL) {

                free(list->firstNode.key);
                free(list->firstNode.value);
                list->firstNode.next = NULL;

            } else {
                                
                free(list->firstNode.key);
                free(list->firstNode.value);

                list->firstNode.key = list->firstNode.next->key;
                list->firstNode.value = list->firstNode.next->value;

                MapListNode *freeNode = list->firstNode.next;

                list->firstNode.next = list->firstNode.next->next;
                free(freeNode);
            }            


        } else {



        }
    }

    return true;
}




//Get value from a key




//Delete the full list
bool map_LL_destroy(MapList *const list) {

    if(list == NULL) {
        return false;
    } else {
    
        MapListNode *currentNode = list->firstNode.next;
        MapListNode *prevNode = list->firstNode.next;

        while(prevNode != NULL) {

            currentNode = currentNode->next;
            free(prevNode->key);
            free(prevNode->value);
            free(prevNode);

            prevNode = currentNode;
        }

        free(list->firstNode.key);
        free(list->firstNode.value);
    }


    return true;
}






















