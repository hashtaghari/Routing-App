#ifndef _STACK_H_
#define _STACK_H_

//Structure for creating a node for a Stack
struct StackNode {
    int data;
    struct StackNode *next;
};

//Making a stack out of array of Stack Nodes
typedef struct StackNode *Stack;

struct StackNode *newNode(int data);
int isEmptyStack(struct StackNode **root);
void push(struct StackNode **root, int data);
int pop(struct StackNode **root);
int peek(struct StackNode **root_ref);
void printstack(Stack *s);


#endif