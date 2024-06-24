//Generic datatypes in C - uses uint8_t to index with bytes directly

#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>


typedef struct Node Node;
typedef struct ListNode ListNode;
typedef struct PriorityNode PriorityNode;


typedef struct LinkedList { //Doubly linked list

    size_t datatypeSize;
    struct ListNode *head;
    struct ListNode *end; //End of the LL (just here for faster push_back)

} LinkedList;
typedef struct Stack {

    size_t datatypeSize;
    struct Node *head;

} Stack;
typedef struct Queue {

    size_t datatypeSize;
    struct Node *head;

} Queue;
typedef struct PriorityQueue {

    size_t datatypeSize;
    struct PriorityNode *head;

} PriorityQueue;

bool stack_initialise(Stack *const stack, size_t dataSize);
size_t stack_length(Stack *const stack);
bool stack_push(Stack *const stack, void *data);
const void* stack_peak(Stack *const stack);
bool stack_pop(Stack *const stack, void *result);

bool LL_print(LinkedList *const linkedList);
bool LL_initialise(LinkedList *const linkedList, size_t dataSize);
size_t LL_length(LinkedList *const linkedList);
bool LL_push_front(LinkedList *const list, void *data);
bool LL_delete_front(LinkedList *const list);


#endif // DATASTRUCTURES_H




