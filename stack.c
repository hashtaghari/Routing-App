#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct StackNode *newNode(int data) {
    struct StackNode *stackNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmptyStack(struct StackNode **root) {
    return !(*root);
}

void push(struct StackNode **root, int data) {
    struct StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

int pop(struct StackNode **root) {
    if (isEmptyStack(root))
        return INT_MIN;
    struct StackNode *temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);

    return popped;
}

int peek(struct StackNode **root_ref) {
    Stack root = *root_ref;
    if (isEmptyStack(&root))
        return INT_MIN;
    return root->data;
}

void printstack(Stack *s) {
    while (!isEmptyStack(s))
    {
        printf("%d ", pop(s));
    }
    printf("\n");
}
