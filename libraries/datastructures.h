//Generic datatypes in C - uses uint8_t to index with bytes directly

#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>


typedef struct Node Node;
typedef struct PriorityNode PriorityNode;


typedef struct LinkedList {

    size_t datatypeSize;
    struct Node *head;
    struct Node *end; //End of the LL (just here for faster push_back)

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
bool stack_push(Stack *const stack, void *data);
const void* stack_peak(Stack *const stack);
bool stack_pop(Stack *const stack, void *result);




#endif // DATASTRUCTURES_H




