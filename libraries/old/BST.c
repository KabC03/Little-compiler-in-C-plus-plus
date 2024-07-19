#include "BST.h"

BinaryTreeNode* create_node(int data) {

    BinaryTreeNode *newNode = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    if(newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}



//Modification
BinaryTreeNode* insert_BST_R(BinaryTreeNode *head, int data) {

    if(head == NULL) {

        head = create_node(data);
        if(head == NULL) {
            return NULL;
        }
        return head;
    }

    if(head->data == data) {
        return NULL; // Not allowed
    } else if(head->data > data) {
        head->left =  insert_BST_R(head->left, data); //Left subtree is less
    } else {
        head->right = insert_BST_R(head->right, data); //Right subtree is more
    }

    return head;
}
BinaryTreeNode* insert_BST(BinaryTreeNode **head, int data) {

    (*head) = insert_BST_R(*head, data);
    return (*head);
}




BinaryTreeNode *get_inorder_successor_BST_R(BinaryTreeNode *head) {
    //Try go left as far as possible
    if(head == NULL) { //Shouldnt happen if being called properly
        return NULL;

    } else if(head->left == NULL) {

        return head;

    } else {
        
        return get_inorder_successor_BST_R(head->left);
    }

    return NULL;
}
BinaryTreeNode *delete_BST_R(BinaryTreeNode *head, int data) {

    BinaryTreeNode *temp = NULL;
    if(head == NULL) {
        return NULL;
    } else {

        if(head->data < data) {

            head->right = delete_BST_R(head->right, data); //Left subtree is more

        } else if(head->data > data) {

            head->left = delete_BST_R(head->left, data); //Left subtree is less

        } else { //Found the node
            
            if(head->left == NULL && head->right == NULL) { //No children nodes

                free(head);
                return NULL;
            } else if(head->left == NULL) { //Left child

                temp = head->right;
                free(head);
                return temp;
            } else if(head->right == NULL) { //Right child

                temp = head->left;
                free(head);
                return temp;
            } else { //Two children - traverse right subtree then go as left as possible

                //Get inorder successor data
                BinaryTreeNode *tempNode = get_inorder_successor_BST_R(head->right); 
                int tempData = tempNode->data;

                //Delete the inorder successor
                head->right = delete_BST_R(head->right, tempData);

                //Assign the head the new data
                head->data = tempData;

                return head;
            }
        }

    }
    return head;
}

bool delete_BST(BinaryTreeNode **head, int data) {

    if((*head) == NULL) {
        return false;
    } else {
        (*head) = delete_BST_R(*head, data);
    }

    return true;
}

//Traverse and print BST
void print_post_order_BST(BinaryTreeNode *head) {

    if(head == NULL) {
        return;

    }

    print_post_order_BST(head->left); //Left subtree is less
    print_post_order_BST(head->right); //Right subtree is more
    printf("%d ", head->data);

    return;
}
void print_in_order_BST(BinaryTreeNode *head) {

    if(head == NULL) {
        return;

    }

    print_in_order_BST(head->left); //Left subtree is less
    printf("%d ", head->data);
    print_in_order_BST(head->right); //Right subtree is more

    return;
}
void print_pre_order_BST(BinaryTreeNode *head) {

    if(head == NULL) {
        return;

    }

    printf("%d ", head->data);
    print_pre_order_BST(head->left); //Left subtree is less
    print_pre_order_BST(head->right); //Right subtree is more

    return;
}



//Search
BinaryTreeNode* search_BST(BinaryTreeNode *head, int data) {

    if(head == NULL) {
        return NULL;
    }

    if(head->data == data) {
        return head;
    } else if(head->data > data) {
        return search_BST(head->left, data); //Left subtree is less
    } else {
        return search_BST(head->right, data); //Right subtree is more
    }


    return NULL;
}


BinaryTreeNode *traverse_direction_BST_R(BinaryTreeNode *head, char direction) {

    BinaryTreeNode *tempNode = NULL;
    if(head == NULL) {
        return NULL;
    } else if(direction == 'l') {

        if(head->left == NULL) {
            return head;
        } else {
            return traverse_direction_BST_R(head->left, 'l');
        }

    } else if(direction == 'r') {

        if(head->right == NULL) {
            return head;
        } else {
            return traverse_direction_BST_R(head->right, 'r');
        }

    } else {
        return NULL;
    }
    return tempNode;
}
int max_BST(BinaryTreeNode *head) { //Find max - go as right as possible
    
    if(head == NULL) {
        return INT_MAX;
    }


    BinaryTreeNode *tempPtr = traverse_direction_BST_R(head, 'r');
    if(tempPtr == NULL) {
        return head->data;
    } else {
        return tempPtr->data;
    }
    return INT_MAX;
}
int min_BST(BinaryTreeNode *head) { //Find min - go as left as possible

    if(head == NULL) {
        return INT_MIN;
    }


    BinaryTreeNode *tempPtr = traverse_direction_BST_R(head, 'l');
    if(tempPtr == NULL) {
        return head->data;
    } else {
        return tempPtr->data;
    }
    return INT_MIN;

}
int size_BST(BinaryTreeNode *head) { //Return number of elements in BST

    if(head == NULL) {
        return 0;

    }


    int count = 1;
    count += size_BST(head->left); //Left subtree is less
    count += size_BST(head->right); //Right subtree is more

    return count;
}



bool export_inorder_BST_R(BinaryTreeNode *head, int *array, int *index) {

    if(array == NULL || index == NULL) {
        return false;
    } else if(head == NULL) {
        return true;
    }

    export_inorder_BST_R(head->left, array, index); //Left subtree is less


    array[*index] = head->data;
    (*index)++;

    export_inorder_BST_R(head->right, array, index); //Right subtree is more

    return true;
}
int *export_inorder_BST(BinaryTreeNode *head) { //Export to array of integers - export inorder traversal

    if(head == NULL) {
        return NULL;
    }

    int treeSize = size_BST(head);
    if(treeSize == 0) {
        return NULL;
    }


    int *array = (int*)malloc(sizeof(int) * treeSize);
    if(array == NULL) {
        return NULL;
    }

    int index = 0; //Pass by reference since by value is more complex
    if(export_inorder_BST_R(head, array, &index) == false) {
        free(array);
        return NULL;
    }

    return array;
}
