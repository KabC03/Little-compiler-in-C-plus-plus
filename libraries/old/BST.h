
#ifndef BST_H
#define BST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef struct BinaryTreeNode {
    //Note values right are greater and values left are less

    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;

} BinaryTreeNode;


//Creation
BinaryTreeNode* insert_BST(BinaryTreeNode **head, int data);
bool delete_BST(BinaryTreeNode **head, int data);

//Searching
void print_post_order_BST(BinaryTreeNode *head);
void print_in_order_BST(BinaryTreeNode *head);
void print_pre_order_BST(BinaryTreeNode *head);

BinaryTreeNode* search_BST(BinaryTreeNode *head, int data);
int max_BST(BinaryTreeNode *head);
int min_BST(BinaryTreeNode *head);
int size_BST(BinaryTreeNode *head);
int *export_inorder_BST(BinaryTreeNode *head);

#endif //BST_H

