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
    struct PriorityNode *back;
};




/**
 * stack_print
 * ===============================================
 * Brief: Print a stack of integers 
 * 
 * Param: *stack - stack of interest
 *
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool stack_print(const Stack *const stack) {

    if(stack == NULL) {
        return false;

    } else {
        
        Node *currentNode = stack->head;

        while(currentNode != NULL) {
           
            printf("%d, ", *(int*)(currentNode->data));

            currentNode = currentNode->next;
        }


    }

    return true;
}



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
bool stack_push(Stack *const stack, const void *const data) {

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
void* stack_peak(Stack *const stack) {

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
bool stack_pop(Stack *const stack, void **const result) {

    if(stack == NULL || result == NULL) {
        return false;
    } else {

        if(stack->head == NULL) {
            *result = NULL;
            return false;


        } else {
            
            *result = stack->head; //NOTE: CALLER MUST FREE THIS POINTER

            stack->head = stack->head->next;
        }

    }

    return true;
}




/**
 * stack_destroy 
 * ===============================================
 * Brief: Destroy a stack 
 * 
 * Param: *stack - stack of interest
 *
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool stack_destroy(Stack *stack) {

    if(stack == NULL) {
        return false;


    } else {
    
        Node *currentNode = stack->head;
        Node *freeNode = stack->head;

        while(freeNode != NULL) {
            currentNode = currentNode->next;
            free(freeNode);
            freeNode = currentNode;
        }

    }


    return true;
}










//Queue


/**
 * queue_print 
 * ===============================================
 * Brief: Print a queue (assumes integers)
 * 
 * Param: *queue - Queue to print 
 * 
 * Return: bool - T/F depending on if list exists
 * 
 */
bool queue_print(const Queue *const queue) {

    if(queue == NULL) {
        return false;

    } else {
        
        Node *currentNode = queue->head;

        while(currentNode != NULL) {
           
            printf("%d, ", *(int*)(currentNode->data));

            currentNode = currentNode->next;
        }


    }

    return true;
}






/**
 * queue_initialise 
 * ===============================================
 * Brief: Initialise a queue 
 * 
 * Param: *queue - Queue to initialise
 *        dataSize - Size of data to be held within the queue
 * 
 * Return: bool - T/F depending on if list exists
 * 
 */
bool queue_initialise(Queue *const queue, const size_t dataSize) {


    if(queue == NULL || dataSize == 0) {
        
        return false;

    } else {

        queue->datatypeSize = dataSize;
        queue->head = NULL;
        queue->tail = NULL;

    }

    return true;
}



/**
 * queue_enqueue 
 * ===============================================
 * Brief: Enqueue an item to a queue 
 * 
 * Param: *queue - Queue to enqueue to 
 *        *data - Data to enqueue
 * 
 * Return: bool - T/F depending on if list exists
 * 
 */
bool queue_enqueue(Queue *queue, const void *const data) {


    if(queue == NULL || data == NULL) {
        return false;
    } else {

        //Allocate space for a new node
        Node *newNode = malloc(sizeof(Node));
        if(newNode == NULL) {
            return false;
        }
        newNode->data = malloc(queue->datatypeSize);
        if(newNode->data ==NULL) {
            free(newNode);
            return false;
        }
        memcpy(newNode->data, data, queue->datatypeSize);

        

        //Insert at the END of the list
        newNode->next = NULL;
        if(queue->head == NULL) { //Queue was empty
            queue->head = newNode;
            queue->tail = newNode;

        } else { //Queue is not empty
            queue->tail->next = newNode;
            queue->tail = newNode;
        }
    }

    return true;
}


/**
 * queue_dequeue
 * ===============================================
 * Brief: Dequeue an item to a queue 
 * 
 * Param: *queue - Queue to enqueue to 
 *        *dataOut - Output data pointer 
 * 
 * Return: bool - T/F depending on if list exists
 * 
 */
bool queue_dequeue(Queue *const queue, void **data) {

    if(queue == NULL || data == NULL) {

        return false;

    } else {

        if(queue->head == NULL) { //Empty queue
            return false;


        } else {
            
            //NOTE: Caller MUST free data pointer - lost reference to it here
            *data = queue->head->data;


            queue->head = queue->head->next;
            if(queue->head == NULL) { //Queue is now empty
                queue->tail = NULL;
            }
        }
    }

    return true;
}



/**
 * queue_destroy
 * ===============================================
 * Brief: Destroy a queue 
 * 
 * Param: *queue - Queue to destroy 
 * 
 * Return: bool - T/F depending on if list exists
 * 
 */
bool queue_destroy(Queue *const queue) {

    if(queue == NULL) {
        return false;
    } else {

        Node *currentNode = queue->head;
        Node *freeNode = queue->head;
        while(freeNode != NULL) {
            
            currentNode = currentNode->next;
            free(freeNode);
            freeNode = currentNode;
        }

        queue->head = NULL;
        queue->tail = NULL;
    }

    return true;
}












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
bool LL_insert_front(LinkedList *const list, const void *const data) {

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
 * LL_insert_back
 * ===============================================
 * Brief: Insert at back of list
 * 
 * Param: *linkedList - linkedList of interest
 *        *data - data to be added
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool LL_insert_back(LinkedList *const list, const void *const data) {

    if(list == NULL || data == NULL) {
        return false;
    } else {

        ListNode *newNode = malloc(sizeof(ListNode));
        if(newNode == NULL) {
            return false;
        }
        newNode->data = malloc(list->datatypeSize);
        if(newNode->data == NULL) {
            return false;
        }
        newNode->back = NULL;
        newNode->next = NULL;


        memcpy(newNode->data, data, list->datatypeSize);
        if(list->end != NULL) {
            
            newNode->back = list->end;
            list->end->next = newNode;
            list->end = newNode;

        } else {

            list->head = newNode;
            list->end = newNode;

        }
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




/**
 * LL_insert_index
 * ===============================================
 * Brief: Insert at an index into the LL 
 * 
 * Param: *linkedList - LinkedList of interest
 *        *data - Data to insert
 *        index - Index to insert
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool LL_insert_index(LinkedList *const list, size_t index,const void *const data) {

    if(list == NULL || data == NULL) {
        return false;
    } else {


        //Check if inserting at front (special case)
        if(index == 0) {
            return LL_insert_front(list, data); //Pass down return value

        }
        //If list was empty, can only insert at index 0 - not allowed to insert anywhere else
        if(list->head == NULL) {
            return false;
        }



        //New node
        ListNode *newNode = malloc(sizeof(ListNode));
        if(newNode == NULL) {
            return false;
        }
        newNode->next = NULL;
        newNode->back = NULL;
        newNode->data = malloc(list->datatypeSize);

        if(newNode->data == NULL) {
            free(newNode);
            return false;
        }
        memcpy(newNode->data, data, list->datatypeSize);



        //Could use double pointer if didnt have to worry about end pointer 
        ListNode *currentNode = list->head;
        for(size_t i = 0; i < index - 1; i++) {

            currentNode = currentNode->next;
            if(currentNode == NULL) { //Index out of bounds
                
                //Check if trying to insert a node at the back
                if(index - i == 1) {
                    if(LL_insert_back(list, data) == false) {
                        return false;
                    }
                    return true;
                }




                return false;
            }
        }
        newNode->back = currentNode;
        newNode->next = currentNode->next;
        
        if(currentNode->next == NULL) {

           //Do nothing 
        } else {

            currentNode->next->back = newNode;
        }
        currentNode->next = newNode;

    }

    return true;
}



/*
TODO:

- Delete at index

- Get item at index
- Get item from start
- Get item from end

- Delete a linked list
- Copy a linked list
*/





//Simple linked list - WARNING UNTESTED
/*
- First node is embedded allowing for quick access without dereference


- Mainly meant to be embedded in other libraries (e.g map)
- Must pass the head NODE  Lnot aL
- Singly linked list

*/
bool map_LL_print(MapList *const list) {

    if(list == NULL) {
        printf("Invalid map\n");
        return false;
    } else {
        printf("Index    || Key || Value\n");

        if(list->firstNode.key != NULL) {

            printf("       0 || %s   || %d \n", (char*)(list->firstNode.key),*(int*)(list->firstNode.value));
        } else{
            printf("NULL\n");
        }


        MapListNode *currentNode = list->firstNode.next;

        int count = 1;
        while(currentNode != NULL) {

            if(list->firstNode.key != NULL) {
                printf("       %d || %s   || %d \n", count,(char*)(currentNode->key),*(int*)(currentNode->value)); 
                    currentNode = currentNode->next;
                    count++;
            } else {
                printf("NULL\n");
            }

        }     
        printf("\n\n");   
    }

    return true;
}



//Initialise
bool map_LL_initialise(MapList *const list) {

    if(list == NULL) {
        return false;
    } else {

        list->firstNode.key = NULL;
        list->firstNode.value = NULL;
        list->firstNode.next = NULL;

    }


    return true;
}


//Insert after first node at the front
bool map_LL_insert_front(MapList *const list, const void *const inputKey, const void *const inputValue, size_t keySize, size_t valueSize) {

    if(list == NULL || inputKey == NULL || inputValue == NULL) {
        return false;
    } else {

        if(list->firstNode.key == NULL) { //Insert at this node

            list->firstNode.key = malloc(keySize);
            if(list->firstNode.key == NULL) {
                return false;
            }
            list->firstNode.value = malloc(valueSize);
            if(list->firstNode.value == NULL) {
                free(list->firstNode.key);
                return false;
            }

            memcpy(list->firstNode.key, inputKey, keySize);
            memcpy(list->firstNode.value, inputValue, valueSize);


        } else { //Insert after first node
            
            MapListNode *newNode = malloc(sizeof(MapListNode));
            newNode->next = list->firstNode.next;

            newNode->key = malloc(keySize);
            if(newNode->key == NULL) {
                free(newNode);
                return false;
            }
            newNode->value = malloc(valueSize);
            if(newNode->value == NULL) {
                free(newNode->key);
                free(newNode);
                return false;
            }


            memcpy(newNode->key, inputKey, keySize);
            memcpy(newNode->value, inputValue, valueSize);

            list->firstNode.next = newNode;
        }
    }


    return true;
}




//Delete by a key
bool map_LL_delete_key(MapList *const list, const void *const inputKey, size_t keySize) {

    if(list == NULL || inputKey == NULL || keySize == 0) {
        return false;
    } else {

        if(memcmp(list->firstNode.key, inputKey, keySize) == 0) {

            if(list->firstNode.next == NULL) {

                free(list->firstNode.key);
                free(list->firstNode.value);
                list->firstNode.next = NULL;
                list->firstNode.key = NULL;
                list->firstNode.value = NULL;

            } else {
                                
                free(list->firstNode.key);
                free(list->firstNode.value);

                list->firstNode.key = list->firstNode.next->key;
                list->firstNode.value = list->firstNode.next->value;

                MapListNode *freeNode = list->firstNode.next;

                list->firstNode.next = list->firstNode.next->next;

                freeNode->key = NULL;
                freeNode->value = NULL;
                free(freeNode);


            }            
            return true;


        } else { //Loop to find the other nodes

            MapListNode *prevNode = &(list->firstNode);
            MapListNode *currentNode = list->firstNode.next;


            while(currentNode != NULL) {
                
                if(memcmp(currentNode->key, inputKey, keySize) == 0) {
                    //Delete the node
                    prevNode->next = currentNode->next;
                    free(currentNode->key);
                    free(currentNode->value);
                    free(currentNode);
                    return true;
                } else {

                    prevNode = currentNode;
                    currentNode = currentNode->next;
                }
            }
        }
    }

    return false; //Key wasnt in the list
}




//Get value from a key - return pointer to value
const void *map_LL_get_value(MapList *const list, const void *const inputKey, size_t keySize) {

    if(list == NULL || inputKey == NULL || keySize == 0) {
        return NULL;
    } else {

        if(list->firstNode.key == NULL) {
            return NULL; //Return NULL ptr if not in list
        }
        if(memcmp(list->firstNode.key, inputKey, keySize) == 0) {
            return list->firstNode.value; 
        }


        MapListNode *currentNode = list->firstNode.next;
        while(currentNode != NULL) {


            if(currentNode->key == NULL) {
                return NULL; //Return NULL ptr if not in list
            }

            if(memcmp(currentNode->key, inputKey, keySize) == 0) {
                return currentNode->value;
            }

            currentNode = currentNode->next;
        }
    }

    return NULL;
}



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
        list->firstNode.key = NULL;
        list->firstNode.next = NULL;
        list->firstNode.value = NULL;
    }


    return true;
}




//Initialise, Set key/value, get value from key, delete value with key, delete full map




//Print a map
void string_map_LL_print(StringMapList *const list) {

    if(list == NULL) {
        printf("NULL\n");
        return;


    } else {

        StringMapListNode *currentNode = list->firstNode;

        while(currentNode != NULL) {

            printf("Key:  '%20s'     || Value:  '%d'       \n",(char*)(currentNode->key), *(int*)(currentNode->value));

            currentNode = currentNode->next;
        }
    }
    return;
}


//Initialise first node
bool string_map_LL_initilise(StringMapList *const list) {

    if(list == NULL) {
        return false;
    } else {

        list->firstNode = NULL;
    }

    return true;
}



//Set key and value pair (insert at front) - note using size_t instead of strlen for saftey
bool string_map_LL_set(StringMapList *const list, const void *const inputKey, const void *const inputValue, size_t inputKeySize, size_t inputValueSize) {

    if(list == NULL || inputKey == NULL || inputValue == NULL || inputKeySize == 0 || inputValueSize == 0) {
        return false;
        
    } else {

        //Search entire LL first before adding new node

        StringMapListNode *currentNode = list->firstNode;
        while(currentNode != NULL) {

            //First check if key size is the same (if its different then they are different)
            if(currentNode->keySize == inputKeySize) {

                if(memcmp(currentNode->key, inputKey, inputKeySize) == 0) {
                    //Found the same key - replace it
                    break;
                }
            }

            currentNode = currentNode->next;
        }


        //Check if actually found a node or skiped the while loop
        if(currentNode == NULL) {

            currentNode = malloc(sizeof(StringMapListNode));
            if(currentNode == NULL) {
                return false;
            }
            
            currentNode->next = list->firstNode; //Set to the head
            currentNode->key = malloc(inputKeySize * sizeof(char));
            currentNode->value = malloc(inputValueSize * sizeof(char));

        } else {
            //Found a node so update it

            currentNode->key = realloc(currentNode->key, inputKeySize * sizeof(char));
            currentNode->value = realloc(currentNode->value, inputValueSize * sizeof(char));

        }


        currentNode->keySize = inputKeySize;
        currentNode->valueSize = inputValueSize;


        if(currentNode->key == NULL || currentNode->value == NULL) {
            return false;
        }
        
        memcpy(currentNode->key, inputKey, inputKeySize);
        memcpy(currentNode->value, inputValue, inputValueSize);
        list->firstNode = currentNode;
        return true;


    }

    return true;
}



//Get a value from a key (could use strlen - but size_t keeps it more generic)
const void *string_map_LL_get_value(StringMapList *const list, const void *const inputKey, size_t inputKeySize) {


    if(list == NULL || inputKey == NULL || inputKeySize == 0) {
        return NULL;
    } else {

        StringMapListNode *currentNode = list->firstNode;
        while(currentNode != NULL) {

            //First check if key size is the same (if its different then they are different)
            if(currentNode->keySize == inputKeySize) {

                if(memcmp(currentNode->key, inputKey, inputKeySize) == 0) {
                
                    return currentNode->value;
                }
            }

            currentNode = currentNode->next;
        
        
        
        }
    }
    
    return NULL;
}




bool string_map_LL_delete_key(StringMapList *const list, const void *const inputKey, size_t inputKeySize) {

    if(list == NULL || inputKey == NULL || inputKeySize == 0) {

        return false;
        
    } else {


        StringMapListNode *currentNode = list->firstNode;
        StringMapListNode *prevNode = list->firstNode;
        while(currentNode != NULL) {

            //First check if key size is the same (if its different then they are different)
            if(currentNode->keySize == inputKeySize) {

                if(memcmp(currentNode->key, inputKey, inputKeySize) == 0) {

                    prevNode->next = currentNode->next;


                    free(currentNode->key);
                    free(currentNode->value);
                    free(currentNode);
                }
            }

            prevNode = currentNode;
            currentNode = currentNode->next;
        
        }

    }

    return true;
}




//Delete an entire list
bool string_map_LL_destroy(StringMapList *const list) {

    if(list == NULL) {
        return false;
    } else {


        StringMapListNode *currentNode = list->firstNode;
        StringMapListNode *prevNode = list->firstNode;

        while(currentNode != NULL) {

            free(prevNode->key);
            free(prevNode->value);
            free(prevNode);

            prevNode = currentNode;
            currentNode = currentNode->next; 
        }

    }
    return true;

    
}




