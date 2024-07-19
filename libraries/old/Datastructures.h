#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

typedef struct node node;
typedef struct queue queue;
typedef struct A_queue A_queue;
typedef struct binTree binTree;

struct node {
    int value;  //Value contained in node
    node * next; //Pointer to next element
    
    int priority; //ONLY USED IN PRIORITY QUEUE
};
struct queue { //Linked list queue
    node * head;
    node * tail;
    
    
};
struct A_queue { //Array queue
    int head;
    int * qPtr;
    int tail;
};

struct binTree {
    int value;  //Value contained in node
    
    binTree * left;
    binTree * right;
};

// Linked list stack
int L_stack_print_length(node * head);
bool L_stack_push(node ** head, int val);
int L_stack_pop(node ** head);
bool L_stack_print(node ** head);


// Linked list functions
void L_print(node *head);
int L_length(node *head);
bool L_insert_front(node **head, int val);
bool L_insert_back(node **head, int val);
bool L_insert_middle(node **head, int val);
bool L_insert_before_index(node **head, int val, int index);
bool L_insert_after_index(node **head, int val, int index);
int L_delete_front(node **head);
int L_delete_back(node **head);
int L_delete_middle(node **head);
int L_delete_index(node **head, int index);
bool L_reverse(node **head);
bool L_compare(node *list1, node *list2);
node *L_copy(node *head);
void L_bubble(node **head);
int L_search(node **head, int value);


// Linked list queue functions
bool L_queue_initialise(queue *ptrs);
bool L_queue_enqueue(queue *ptrs, int val);
int L_queue_dequeue(queue *ptrs);
bool L_queue_print(queue *ptrs);

// Priority queue function
bool L_queue_priority_enqueue(queue *ptrs, int val, int priority);
int L_queue_dequeue_priority(queue *ptrs, int priority);
