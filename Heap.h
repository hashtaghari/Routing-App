#ifndef _HEAP_HEADER_
#define _HEAP_HEADER_

#include<stdbool.h>
#include<stdlib.h>
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

//Functions related to heap.

//Creates a new heap node with given data and returns its pointer.
struct MinHeapNode *newMinHeapNode(int v, int dist);

//Creates a new heap of given capacity and returns pointer to its head.
struct MinHeap *createMinHeap(int capacity);

//Swaps 2 nodes of a heap.
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b);

//Minimum heapifys a given heap for provided index. 
void minHeapify(struct MinHeap *minHeap, int idx);

//Returns TRUE if heap is empty.
int isEmpty(struct MinHeap *minHeap);

//Standard function to extract the minimum element from heap.
struct MinHeapNode *extractMin(struct MinHeap *minHeap);

//Function to decreasy dist value of a given vertex v. This function uses pos[] of min heap to get the current index of node in min heap.
void decreaseKey(struct MinHeap *minHeap, int v, int dist);

//A utility function to check if a given vertex 'v' is in min heap or not.
bool isInMinHeap(struct MinHeap *minHeap, int v);


#endif