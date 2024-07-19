//Generic datatypes in C - uses uint8_t to index with bytes directly

#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>




typedef struct MapListNode {

    uint8_t *key;
    uint8_t *value;
    struct MapListNode *next;

} MapListNode;
typedef struct StringMapListNode {

    size_t keySize;
    size_t valueSize;


    uint8_t *key;
    uint8_t *value;
    struct StringMapListNode *next;

} StringMapListNode;


typedef struct Node Node;
typedef struct ListNode ListNode;
typedef struct PriorityNode PriorityNode;



typedef struct MapList{ //Small Singly linked LL (first node stored in list itself)

    struct MapListNode firstNode;

} MapList;
typedef struct StringMapList {

    struct StringMapListNode *firstNode; //First node not embeded (for now)

} StringMapList;



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
bool stack_push(Stack *const stack, const void *const data);
void* stack_peak(Stack *const stack);
bool stack_pop(Stack *const stack, void *result);

bool LL_print(LinkedList *const linkedList);
bool LL_initialise(LinkedList *const linkedList, size_t dataSize);
size_t LL_length(LinkedList *const linkedList);
bool LL_insert_front(LinkedList *const list, const void *const data);
bool LL_delete_front(LinkedList *const list);
bool LL_insert_back(LinkedList *const list, const void *const data);
bool LL_delete_back(LinkedList *const list);
bool LL_insert_index(LinkedList *const list, size_t index,const void *const data);







bool map_LL_print(MapList *const list);
bool map_LL_initialise(MapList *const list); 
bool map_LL_insert_front(MapList *const list, const void *const inputKey, const void *const inputValue, size_t keySize, size_t valueSize);
bool map_LL_delete_key(MapList *const list, const void *const inputKey, size_t keySize);
const void *map_LL_get_value(MapList *const list, const void *const inputKey, size_t keySize);
bool map_LL_destroy(MapList *const list);



void string_map_LL_print(StringMapList *const list);
bool string_map_LL_initilise(StringMapList *const list);
bool string_map_LL_set(StringMapList *const list, const void *const inputKey, const void *const inputValue, size_t inputKeySize, size_t inputValueSize);
const void *string_map_LL_get_value(StringMapList *const list, const void *const inputKey, size_t inputKeySize);
bool string_map_LL_delete_key(StringMapList *const list, const void *const inputKey, size_t inputKeySize);
bool string_map_LL_destroy(StringMapList *const list);

#endif // DATASTRUCTURES_H



