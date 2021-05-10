#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//Function for creating a node for a stack.
struct StackNode *newNode(int data) {
    struct StackNode *stackNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

//Utility function to check whether a given stack is empty.
int isEmptyStack(struct StackNode **root) {
    return !(*root);
}

//Function to add an element to the start of a Stack.
void push(struct StackNode **root, int data) {
    struct StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

//Function to remove an element from the start of a Stack.
int pop(struct StackNode **root) {
    if (isEmptyStack(root))
        return INT_MIN;
    struct StackNode *temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);

    return popped;
}

//Function to fetch the name of the edge given to the starting node and ending node.
int peek(struct StackNode **root_ref) {
    Stack root = *root_ref;
    if (isEmptyStack(&root))
        return INT_MIN;
    return root->data;
}

//Utility function to print out the elements of a stack/
void printstack(Stack *s) {
    while (!isEmptyStack(s))
    {
        printf("%d ", pop(s));
    }
    printf("\n");
}
