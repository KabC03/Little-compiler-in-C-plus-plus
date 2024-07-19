#include "Datastructures Plus.h"
#define STACK_SIZE 5

//Stack datastructure:

    //Linked list
int L_stack_print_length(node * head) { //Return stack length
    
    if(head == NULL) return INT_MIN;
    
    node * currentPtr = head;
    int length = 1;
    while (currentPtr->next != NULL) {
        currentPtr = currentPtr->next;
        length++;
    }

    return length;
}
bool L_stack_push(node ** head, int val) { //Push onto stack
    /*
     head - pointer to list head
     value - value to push on stack
     
     returns false on failure and true on success
     */

    node * newPtr = malloc(sizeof(node));
    if(newPtr == NULL || val == INT_MIN) return false;
    newPtr->value = val;
    newPtr->next = *head;
    *head = newPtr;
    
    return true;
}
int L_stack_pop(node ** head) { //Pop and return from stack
    /*
     head - pointer to list head
     value - value to push on stack
     
     returns INT_MIN on failure and value on success
     */
    
    if((*head) == NULL) return INT_MIN;
    
    int returnVal = (*head)->value;
    node * nodePtr = *head;
    *head = (*head)->next;
    free(nodePtr);
    
    return returnVal;
}
bool L_stack_print(node ** head) { //Print entire stack
    /*
     head - pointer to lsit head
     
     returns false on failure and true on success
     */
    
    if(*head == NULL) {
        printf("NULL\n");
        return false;
    }
    
    node * currentPtr = (*head);
    
    while (currentPtr->next != NULL) {
        printf("%d - ",currentPtr->value);
        currentPtr = currentPtr->next;
    }
    printf("%d - NULL\n",currentPtr->value);
    
    return true;
}
            
            /*
             //Example script:
             
             node * head = NULL;
             int num = 10;
             
             for (int i = 0; i < num; i++) {
                 lpush(&head, i);
             }
             printf("Length: %d\n",spLen(head));
             
             for (int i = 0; i < num; i++) {
                 
                 if (i == num-1) {
                     printf("%d \n",lpop(&head));
                     break;
                 }
                 
                 printf("%d - ",lpop(&head));
                 
             }
             
             
             */

    //Array
        //Statically allocated stacks - fixed size
int stack[STACK_SIZE];
int head = -1;
bool A_stack_push(int value) { //Push onto stack
    
    if(head == STACK_SIZE) return false;
    
    head++;
    stack[head] = value;

    return true;
}
int A_stack_pop(void) { //Pop and return from stack
    
    if(head == -1) return false;
    int returnVal = stack[head];

    head--;
    return returnVal; //EXPERIMENTAL
}
bool A_stack_print(void) { //Print entire stack
    
    if(head == -1) {
        printf("null\n");
        return false;
    }
    
    for (int i = 0; i < STACK_SIZE - 1; i++) {
        printf("%d - ",stack[i]);
    }
    printf("%d\n",stack[STACK_SIZE - 1]);
    
    return true;
}

        //Dynamicly allocated stacks - dynamic size
int * A_stack_dynamic_create(int stackSize) { //Create array stack
    
    int * stackPtr = calloc((stackSize + 2), sizeof(int));
    if(stackPtr == NULL) return NULL;
    
    stackPtr[0] = stackSize + 1; //Size of stack at index 0;
    stackPtr[1] = 1; //Head index
    
    return stackPtr;
}
int * A_stack_dynamic_push(int * stackPtr, int value) { //Push to stack
    
    if(stackPtr == NULL) return NULL;
    if(stackPtr[1] == stackPtr[0]|| stackPtr == NULL) return NULL;
    
    stackPtr[1]++;
    stackPtr[stackPtr[1]] = value;
    return stackPtr;
}
int A_stack_dynamic_pop(int * stackPtr) { //Pop from stack
    
    if(stackPtr[1] <= 1 || stackPtr == NULL) return INT_MIN;
    
    stackPtr[1]--;
    
    int returnVal = stackPtr[stackPtr[1] + 1];
    
    stackPtr[stackPtr[1] + 1] = 0;
    
    return returnVal;
}
bool A_stack_dynamic_destroy(int * stackPtr) { //Destroy stack
    if(stackPtr == NULL) {
        printf("null\n");
        return false;
    }
    
    free(stackPtr);
    return true;
}
bool A_stack_dynamic_print(int * stackPtr) { //Print stack
    
    if(stackPtr == NULL) {
        printf("null\n");
        return false;
    }
    
    for (int i = 2; i < stackPtr[0]; i++) {
        printf("%d - ",stackPtr[i]);
    }
    printf("%d\n",stackPtr[stackPtr[0]]);
    return true;
}
    /*
     int * stack = acStack(10);
     
     //for (int i = 0; i < 10; i++) {
     //    if(acpush(stack, i) == false) printf("Overflow (%d)\n",i);
     //}
     
     
     acpush(stack, 10);
     acpush(stack, 5);
     printf("%d\n",acpop(stack));
     printf("%d\n",acpop(stack));
     
     
     paStack(stack);
     return 0;
     */


//Linked list datastructure:
void L_print(node * head) { //Print list
    
    if(head == NULL) {
        printf("NULL\n");
        return;
    }
    
    while (head->next != NULL) {
        printf("%d - ",head->value);
        head = head->next;
    }
    printf("%d - NULL\n",head->value);
    
    
    return;
}
int L_length(node * head) { //Return list length
    
    if(head == NULL) return INT_MIN;
    
    node * currentPtr = head;
    int length = 1;
    while (currentPtr->next != NULL) {
        currentPtr = currentPtr->next;
        length++;
    }

    return length;
}
bool L_insert_front(node ** head, int val) { //Insert node at front
    /*
     head - pointer to list head
     value - value to insert
     
     returns false on failure and true on success
     */
    node * nodePtr = malloc(sizeof(node));
    if(nodePtr == NULL) return false;
    
    nodePtr->next = *head;
    nodePtr->value = val;
    (*head) = nodePtr;

    return true;
}
bool L_insert_back(node ** head, int val) { //Insert node at back
    /*
     head - pointer to list head
     value - value to insert
     
     returns false on failure and true on success
     */
    node * nodePtr = malloc(sizeof(node));
    if(nodePtr == NULL) return false;
    
    if(*head == NULL) {
        nodePtr->next = *head;
        nodePtr->value = val;
        (*head) = nodePtr;
        return true;
    }
    
    node * currentPtr = *head;
    while (currentPtr->next != NULL) {
        currentPtr = currentPtr->next;
    }

    nodePtr->value = val;
    nodePtr->next = NULL;
    currentPtr->next = nodePtr;


    return true;
}
bool L_insert_middle(node ** head, int val) { //Insert node in middle
    /*
     head - pointer to list head
     value - value to insert
     
     returns false on failure and true on success
     */
    node * nodePtr = malloc(sizeof(node));
    if(nodePtr == NULL) return false;
    
    
    if((*head) == NULL) {
        nodePtr->next = *(head);
        nodePtr->value = val;
        (*head) = nodePtr;
        return true;
    }
    node * currentPtr = (*head);
    int stop = 0;
    while(currentPtr->next != NULL) {
        stop++;
        currentPtr = currentPtr->next;
        
    }
    stop = (stop)/2; //Adjust position for odd lengths
    //stop = (stop - 1)/2;
    
    
    currentPtr = (*head);
    for (int i = 0; i < stop; i++) {
        currentPtr = currentPtr->next;
        // On first loop currentPtr points to what head does
        // Therefore currentPtr->next points to second element
    }
    nodePtr->next = currentPtr->next;
    nodePtr->value = val;
    currentPtr->next = nodePtr;
    
    return true;
}
bool L_insert_before_index(node ** head, int val, int index) { //Insert BEFORE index
    /*
     head - pointer to list head
     value - value to insert
     
     returns false on failure and true on success
     */
    node * nodePtr = malloc(sizeof(node));
    if(nodePtr == NULL) return false;
    
    
    if((*head) == NULL && (index == 0 || index == 1)) {
        nodePtr->next = *(head);
        nodePtr->value = val;
        (*head) = nodePtr;
        return true;
    }
    if(index == 0 || index == 1) {
        nodePtr->next = (*head);
        nodePtr->value = val;
        (*head) = nodePtr;
        return true;
    }
    node * currentPtr = (*head);
    for (int i = 0; i < index - 1; i++) { //EXPERIMENTAL
        if(currentPtr == NULL) return false;
        currentPtr = currentPtr->next;

        
    }
    if(currentPtr == NULL) return false;
    nodePtr->next = currentPtr->next;
    nodePtr->value = val;
    currentPtr->next = nodePtr;
    
    return true;
}
bool L_insert_after_index(node ** head, int val, int index) { //Insert AFTER index
    /*
     head - pointer to list head
     value - value to insert
     
     returns false on failure and true on success
     */
    node * nodePtr = malloc(sizeof(node));
    if(nodePtr == NULL) return false;
    
    
    if((*head) == NULL && index == 0) {
        nodePtr->next = *(head);
        nodePtr->value = val;
        (*head) = nodePtr;
        return true;
    }
    node * currentPtr = (*head);
    for (int i = 0; i <= index - 1; i++) {
        if(currentPtr == NULL) return false;
        currentPtr = currentPtr->next;

    }

    nodePtr->next = currentPtr->next;
    nodePtr->value = val;
    currentPtr->next = nodePtr;
    
    return true;
}
int L_delete_front(node ** head) { //Delete and return from front of list
    
    if((*head) == NULL) return INT_MIN;
    
    node * freeNode = (*head);
    int returnVal = (*head)->value;
    (*head) = (*head)->next;
    free(freeNode);
    
    return returnVal;
}
int L_delete_back(node ** head) { //Delete and return from back of list
    
    if((*head) == NULL) return INT_MIN;
    
    int returnVal = INT_MIN;
    node * currentPtr = (*head);
    node * prevPtr = (*head);
    while(currentPtr->next != NULL) {
        prevPtr = currentPtr;
        currentPtr = currentPtr->next;
    }
    if(currentPtr != NULL) {
        returnVal = currentPtr->value;
        free(currentPtr);
        prevPtr->next = NULL;
    }

    
    return returnVal;
}
int L_delete_middle(node ** head) { //Delete and return from middle of list
    
    if((*head) == NULL) return INT_MIN;
    
    int listLen = 0;
    node * currentPtr = (*head);
    while (currentPtr->next != NULL) {
        currentPtr = currentPtr->next;
        listLen++;
    }
    
    
    listLen/=2; //Adjust position
    //listLen = (listLen+1)/2;
    int returnVal = INT_MIN;
    
    if (listLen < 1) {
        
        returnVal = L_delete_front(head); //Experimental
        
    }
    else if(listLen >= 1) {
        
        currentPtr = (*head);
        for (int i = 0; i < listLen - 1; i++) {
            currentPtr = currentPtr->next;
        }
        
        node * returnPtr = currentPtr->next;
        returnVal = (currentPtr->next)->value;
        currentPtr->next = (currentPtr->next)->next;
        
        free(returnPtr);
    }
    
    
    return returnVal;
}
int L_delete_index(node ** head, int index) { //Delete and return at index
    
    if((*head) == NULL) return INT_MIN;
    
    node * currentPtr = (*head);
    for (int i = 0; i < (index - 1); i++) {
        currentPtr = currentPtr->next;
        
        if(currentPtr == NULL) return INT_MIN;
    }
    

    node * deletePtr = currentPtr->next;
    int returnVal = deletePtr->value;
    currentPtr->next = deletePtr->next;
    
    free(deletePtr);
    return returnVal;
}
bool L_reverse(node ** head) { //Reverse list
    
    if((head) == NULL) return false;
    
    
    node * prevPtr = (*head);
    node * currentPtr = (*head)->next;
    node * nextPtr = NULL;
    prevPtr->next = NULL;
    
    if(currentPtr != NULL){
        nextPtr = currentPtr->next;
        
        
        while(currentPtr->next != NULL) {
            
            
            currentPtr->next = prevPtr;
            
            prevPtr = currentPtr;
            currentPtr = nextPtr;
            nextPtr = nextPtr->next;
            
        }
        currentPtr->next = prevPtr;
        (*head) = currentPtr;
    }
    
    return true;
}
bool L_compare(node *list1, node *list2) { //Compare if 2 lists are the same
    
    node *current1 = list1;
    node *current2 = list2;

    while(1) {

        if(current1 == NULL && current2 == NULL) {
            return true;
        
        } else if(current1 == NULL || current2 == NULL) {
            return false;

        } else if(current1->value != current2->value) {
            return false;
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    return true;
}
node *L_copy(node *head) { //Copy a list

    node *newHead = NULL;

    if(head == NULL) {
        return NULL;
    } else {

        
        node *copy = NULL;


        copy = malloc(sizeof(node));
        if(copy == NULL) {
            return NULL;
        }
        newHead = copy;
        copy->value = head->value;
        copy->next = NULL;
        node *prevCopy = copy;
        
        node *current = head->next;
        while(current != NULL) {

            copy = malloc(sizeof(node));
            if(copy == NULL) {
                return NULL;
            }
            prevCopy->next = copy;
            copy->value = current->value;

            prevCopy = copy;
            current = current->next;
        }
    }



    return newHead;
}
void L_bubble(node **head) { //Sort a list

    if(head == NULL) {
        return;
    }
    node *prevPtr = *head;
    node *currentPtr = *head;
    bool swapped = true;
    int temp = 0;

    while(swapped == true) {

        swapped = false;
        prevPtr = *head;
        currentPtr = *head;
        while(currentPtr != NULL) {

            if(prevPtr->value > currentPtr->value) {
                swapped = true;
                temp = prevPtr->value;

                prevPtr->value = currentPtr->value;
                currentPtr->value = temp;
            }

            prevPtr = currentPtr;
            currentPtr = currentPtr->next;
        }

    }

    return;
}
int L_search(node **head, int value) { //Search for value in list, return index

    if(head == NULL) {
        return INT_MIN;
    } else {

        node *currentPtr = (*head);
        for(int i = 0; currentPtr != NULL; i++) {

            if(currentPtr->value == value) {
                return i;
            }

            currentPtr = currentPtr->next;
        }
    }

    return INT_MIN;
}
    /*
     Example script:
     
     
     node * headBack = NULL;
     node * headFront = NULL;
     
     
     for (int i = 0; i < 10; i++) {
         iback(&headBack,i);
         ifront(&headFront,i);
     }
     
     
     imiddle(&headBack, 99);
     ibIndex(&headBack, 990, 9);
     iaIndex(&headBack, 99, 0);
     
     
     node * head = NULL;
     
     
     for (int i = 0; i < 10; i++) {
         iback(&head, i);
     }
     
     iback(&head, 10);
     
     lpList(head);
     lrev(&head);
     lpList(head);
      
     //lpList(headBack);
     //printf("Deleted FIRST node with value: '%d'\n",dfront(&headFront));
     //printf("Deleted LAST node with value: '%d'\n",dback(&headFront));
     //printf("Deleted MIDDLE node with value: '%d'\n",dmiddle(&headFront));
     //ifront(&headFront,1);
     //lpList(headFront);
     //printf("Deleted node with value: '%d'\n",dmiddle(&headFront));

     //printf("'%d'\n",dIndex(&headFront, 8));
     //lpList(headFront);
     
     printf("List is %d units long\n",lpLen(headFront));
     */


//Queues
    //Linked list
        //Standard queue
bool L_queue_initialise(queue * ptrs) { //Initialise queue
    
    ptrs->head = NULL;
    ptrs->tail = NULL;
    return true;
}
bool L_queue_enqueue(queue * ptrs, int val) { //Enqueue
    
    node * newNode = malloc(sizeof(node));
    if(newNode == NULL) return false;
    newNode->value = val;
    newNode->next = NULL;
    
    
    if(ptrs->tail != NULL) { //If tail present
        ptrs->tail->next = newNode;
    }
    ptrs->tail = newNode;
    if(ptrs->head == NULL) { //If this is first enqueue
        
        ptrs->head = newNode;
    }
    return true;
}
int L_queue_dequeue(queue * ptrs) { //Dequeue and return
    

    node * nextPtr = NULL;
    
    if(ptrs->head == NULL) return INT_MIN;
    
    int returnVal = ptrs->head->value;
    if(ptrs->head->next == NULL) { //Not last element in queue
        ptrs->head = NULL;
        ptrs->tail = NULL;
    }
    else { //Last element in queue
        nextPtr = ptrs->head->next;
        free(ptrs->head);
        ptrs->head = nextPtr;
        
        
    }
    
    return returnVal;
}
bool L_queue_print(queue * ptrs) { //Print queue
    
    node * currentPtr = ptrs->head;
    while(currentPtr != NULL) {
        
        printf("%d - ",currentPtr->value);
        currentPtr = currentPtr->next;
    }
    printf("null\n");
    
    return true;
}
    
    /*
     queue ptrs;
     liq(&ptrs);
     
     for (int i = 0; i < 10; i++) {
         leq(&ptrs,i);
     }
     lpq(&ptrs);
     while(ptrs.tail != NULL) {
         printf("%d - ",ldq(&ptrs));
     }
     printf("%d - ",ldq(&ptrs)); //Error
     printf("null");
    
     printf("\n");
     */

            //Priority queue
bool L_queue_priority_enqueue(queue * ptrs, int val, int priority) { //Enqueues elements with a priority. Low priority - low number ,High priority - high number
    
    node * newNode = malloc(sizeof(node));
    if(newNode == NULL) return false;
    newNode->value = val;
    newNode->priority = priority;
    
    if(ptrs->tail == NULL) { //Empty queue
        ptrs->tail = newNode;
        ptrs->head = newNode;
        newNode->next = NULL;
        return true;
    }
    else if(priority > ptrs->head->priority) { //Highest priority
        
        newNode->next = ptrs->head;
        ptrs->head = newNode;
    }
    else {
        node * currentPtr = ptrs->head;
        while (currentPtr->next != NULL && priority <= currentPtr->next->priority) {
            currentPtr = currentPtr->next;
        }
        newNode->next = currentPtr->next;
        currentPtr->next = newNode;

        if (newNode->next == NULL) { // Update tail if newNode is now the last node
            ptrs->tail = newNode;
        }
    }

    return true;
}
int L_queue_dequeue_priority(queue * ptrs, int priority) {  //Dequeues the first instance of a priority or higher
    
    if(ptrs->head == NULL) return INT_MIN;
    
    node * currentNode = ptrs->head;
    node * prevNode = ptrs->head;
    while (currentNode->priority > priority)
    {
        prevNode = currentNode;
        currentNode = currentNode->next;
        if(currentNode == NULL) return INT_MIN;
    }
    if(currentNode == NULL) return INT_MIN;

    int returnVal = currentNode->value;

    if (currentNode == ptrs->head)
    {
 
        ptrs->head = currentNode->next;
        free(currentNode);
    }
    else if (currentNode == ptrs->tail)
    {
        ptrs->tail = prevNode;
        free(currentNode);
        ptrs->tail->next = NULL;
    }
    else
    {
        prevNode->next = prevNode->next->next;
        free(currentNode);
    }
    


    return returnVal;
}


    /*
     
     queue q1;
     
     liq(&q1);
     
     
     lpeq(&q1, 0, 0);
     lpeq(&q1, 0, 0);
     lpeq(&q1, 0, 0);
     lpeq(&q1, 0, 0);
     
     
     
     lpeq(&q1, 1, 1);
     lpeq(&q1, 1, 1);
     lpeq(&q1, 1, 1);
     lpeq(&q1, 3, 3);
     lpeq(&q1, 3, 3);
     lpeq(&q1, 3, 3);
     lpeq(&q1, 2, 2);
     
     lpeq(&q1, -1, -1);
     lpeq(&q1, 1, 1);

     lpq(&q1);

     while(1) {
         int val = ldq(&q1);
         
         if(val == INT_MIN) break;
         
         printf("Returning: %d\n",val);

     }
     
     printf("\n");
      


    L_queue_initialise(&q1);
    L_queue_priority_enqueue(&q1, 1, 1);
    L_queue_priority_enqueue(&q1, 1, 1);
    L_queue_priority_enqueue(&q1, 5, 5);
    L_queue_priority_enqueue(&q1, 1, 1);
    L_queue_priority_enqueue(&q1, 1, 1);
    L_queue_print(&q1);

    printf("Int: %d\n", L_queue_dequeue_priority(&q1, 1));
    printf("Int: %d\n", L_queue_dequeue(&q1));



    return 0;



     */


    //Array
bool A_queue_initialise(A_queue * ptrs, int size) { //Initialise queue
    
    ptrs->qPtr = malloc(sizeof(int) * (size + 1));
    if(ptrs->qPtr == NULL) return false;
    
    ptrs->qPtr[0] = size + 1;
    ptrs->head = 0;
    ptrs->tail = 0;
    
    return true;
}
bool A_queue_enqueue(A_queue * ptrs, int val) { //Enqueue

    if(ptrs->tail == 0) { //No elements in queue
        ptrs->head = 1;
        ptrs->tail = 1;
        ptrs->qPtr[ptrs->tail] = val;
    }
    else if(ptrs->tail < ptrs->qPtr[0]) { //Middle of queue
        
        if(ptrs->head == ptrs->tail + 1) {
            return false;
        }
        
        ptrs->tail++;
        ptrs->qPtr[ptrs->tail] = val;

    }
    else if(ptrs->tail == ptrs->qPtr[0]) { //End of queue
        
        if(ptrs->head == 1) {
            return false;
        }
        
        ptrs->tail = 1;
        ptrs->qPtr[ptrs->tail] = val;
    }
    else {
        return false;
    }
    
    return true;
}
int A_queue_dequeue(A_queue * ptrs) { //Dequeue and return

    int returnVal = INT_MIN;
    
    
    //printf("\n\nRecieved: head == %d| tail == %d | qptr == %d\n\n",ptrs->head,ptrs->tail,ptrs->qPtr[0]);
    if(ptrs->head == 0) return returnVal; //Empty queue

    
    else if(ptrs->head < ptrs->qPtr[0] - 1) { //Middle of queue
        
        if(ptrs->head == ptrs->tail) {
            returnVal = ptrs->qPtr[ptrs->head];
            
            ptrs->qPtr[ptrs->head] = 0; //DEBUG
            ptrs->head = 0;
            ptrs->tail = 0;
        }
        else {
            returnVal = ptrs->qPtr[ptrs->head];
            
            ptrs->qPtr[ptrs->head] = 0; //DEBUG
            ptrs->head++;
        }
    }
    else if(ptrs->head + 1 == ptrs->qPtr[0]) {
        
        if(ptrs->head == ptrs->tail) {
            returnVal = ptrs->qPtr[ptrs->head];
            
            ptrs->qPtr[ptrs->head] = 0; //DEBUG
            ptrs->head = 0;
            ptrs->tail = 0;
        }
        
        else if(ptrs->tail == 1) {
            returnVal = ptrs->qPtr[ptrs->head];
            
            ptrs->qPtr[ptrs->head] = 0; //DEBUG
            ptrs->head = 0;
            ptrs->tail = 0;
        }
        else {
            returnVal = ptrs->qPtr[ptrs->head];
            
            ptrs->qPtr[ptrs->head] = 0; //DEBUG
            ptrs->head = 1;
        }
    }
    return returnVal;
}
void A_queue_print(A_queue * ptrs) { //Print queue
    
    for (int i = 1; i < ptrs->qPtr[0]; i++) {
        printf("%d - ",ptrs->qPtr[i]);
    }
    printf("null || head: %d | tail: %d\n",ptrs->head, ptrs->tail);
}
int A_queue_length(A_queue * ptrs) { //Return length of queue
    
    return ptrs->qPtr[0] - 1;
}
    /*
     queuea q1;
     
     int size = 10;
     
     
     aiq(&q1,size);
     
     printf("Queue length: %d\n\n",alq(&q1));
     
     
     for (int i = 0; i < size; i++) {
         aeq(&q1, i);
         //apq(&q1);
     }
     
     //printf("\nT/F: %d\n", aeq(&q1, 99));
     //apq(&q1);
     
     //printf("\n\n");
     
     for (int i = 0; i < size/2; i++) {
         //printf("%d - ",adq(&q1));
         
         //adq(&q1);
         printf("|%d|       ",adq(&q1));
         apq(&q1);
     }
     
     int i = 0;
     while(aeq(&q1, 99 - i) == true) {
         i++;
     }
     
     printf("\n\n\n\n\n\n\n\n\n\n");
     apq(&q1);
     printf("NEW STUFF\n");
     //printf("null\n");
     
     
     int loopVal = 0;
     while(loopVal != INT_MIN) {
         
         loopVal = adq(&q1);
         printf("|%d|       ", loopVal);
         apq(&q1);
         
     }
     return 0;
     */
