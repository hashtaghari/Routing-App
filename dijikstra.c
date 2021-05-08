#include "graph.h"
#include "Heap.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void givepath(int parent[], int j, int *len, int *path)
{
    // *(len)++;
    if (parent[j] == -1)
    {
        return;
    }
    givepath(parent, parent[j], len, path);
    printf("%d ", j);
}

int *dijikstra(struct Graph *graph, int src, int dest, int *len)
{
    int V = graph->V;

    int dist[V];
    int sptset[V];
    int parent[V];

    struct MinHeap *minHeap = createMinHeap(V);

    parent[src] = -1;

    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // minHeap->array[src] = newMinHeapNode(src, dist[src]);
    // minHeap->pos[src] = src;

    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    while (!isEmpty(minHeap))
    {

        struct MinHeapNode *minHeapNode = extractMin(minHeap);

        int u = minHeapNode->v;

        struct Edge *pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;

            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->congestion + dist[u] < dist[v])
            {
                //relexation
                dist[v] = dist[u] + pCrawl->congestion;
                //changing parent of given node
                parent[v] = u;
                //decreasing cost to reach in heap
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    int *path = (int *)malloc(sizeof(int) * V);

    givepath(parent, dest, len, path);
    return path;
}

// int main()
// {
//     int V = 9;
//     struct Graph *graph = createGraph(V);
//     addEdge(graph, 0, 1, 4, "a", 1);
//     addEdge(graph, 0, 7, 8, "a", 1);
//     addEdge(graph, 1, 7, 11, "a", 1);
//     addEdge(graph, 1, 2, 8, "a", 1);
//     addEdge(graph, 7, 8, 7, "a", 1);
//     addEdge(graph, 7, 6, 1, "a", 1);
//     addEdge(graph, 2, 8, 2, "a", 1);
//     addEdge(graph, 8, 6, 6, "a", 1);
//     addEdge(graph, 2, 3, 7, "a", 1);
//     addEdge(graph, 2, 5, 4, "a", 1);
//     addEdge(graph, 6, 5, 2, "a", 1);
//     addEdge(graph, 3, 5, 14, "a", 1);
//     addEdge(graph, 3, 4, 9, "a", 1);
//     addEdge(graph, 5, 4, 10, "a", 1);

//     int src = 2;
//     int len = 0;
//     int *next_vertex = dijikstra(graph, src, 7, &len);

//     // printf("%d", len);
//     // for (int i = 0; i < len; i++)
//     // {
//     //     printf("here");
//     //     printf("%d ", next_vertex[i]);
//     // }
//     // showlist(graph);
// }