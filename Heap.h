#ifndef _HEAP_HEADER_
#define _HEAP_HEADER_

#include<stdbool.h>

struct MinHeapNode
{
    int v;
    int dist;
    char *name;
};
struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

// functions related to heap

struct MinHeapNode *newMinHeapNode(int v, int dist);//creates a new heap node with given data and returns its pointer

struct MinHeap *createMinHeap(int capacity);//creates a new heap of given capacity and returns pointer to its head

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b);//swaps 2 nodes of a heap

void minHeapify(struct MinHeap *minHeap, int idx);//minimum heapifys a given heap for provided index 

int isEmpty(struct MinHeap *minHeap);//returns TRUE if heap is empty

struct MinHeapNode *extractMin(struct MinHeap *minHeap);//Standard function to extract the minimum element from heap

void decreaseKey(struct MinHeap *minHeap, int v, int dist);//Function to decreasy dist value of a given vertex v. This function uses pos[] of min heap to get the current index of node in min heap

bool isInMinHeap(struct MinHeap *minHeap, int v);//A utility function to check if a given vertex 'v' is in min heap or not


#endif