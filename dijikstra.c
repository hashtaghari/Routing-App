#include "graph.h"
#include "Heap.h"
#include "stack.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

//returns a stack data type with top element being next node to travel from src to reach dest most effectively
Stack dijikstra(struct Graph *graph, int src, int dest) {
    
    //Signifies the number of vertices in the graph.
    int V = graph->V;

    //
    int dist[V];
    int sptset[V];
    int parent[V];

    //The minHeap structure being formed so as to sort out the graph and its nodes to implement Djikstra's algorithm.
    struct MinHeap *minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {

        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
        parent[v] = v;

    }

    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    //Implementing Djikstra using a while loop.
    while (!isEmpty(minHeap)) {

        //The minHeap node being formed to remove the final element in the said MinHeap.
        struct MinHeapNode *minHeapNode = extractMin(minHeap);

        int u = minHeapNode->v;

        struct Edge *pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->congestion + dist[u] < dist[v]) {
                //Relaxation.
                dist[v] = dist[u] + pCrawl->congestion;
                //Changing parent of given node.
                parent[v] = u;
                //Decreasing cost to reach in heap.
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    Stack s = NULL;
    int j = dest;

    while (parent[j] != j) {
        push(&s, j);
        j = parent[j];
    }
    return s;
}

//Code used to check whether the algorithm worked at its basis.
// int main()
// {
//     int V = 5;
//     struct Graph *graph = createGraph(V);
//     addEdge(graph, 0, 1, 5, "a", 0);
//     addEdge(graph, 0, 2, 4, "a", 0);
//     addEdge(graph, 1, 2, 2, "a", 0);
//     addEdge(graph, 1, 3, 6, "a", 0);
//     addEdge(graph, 2, 3, 3, "a", 0);

//     int src = 0;

//     Stack s2 = dijikstra(graph, src, 3);

//     while (!isEmptyStack(&s2))
//     {
//         printf("%d ", pop(&s2));
//     }
// }