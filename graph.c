#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

struct Edge *newEdge(int dest, int Length, char *name) //return a new edge with given properties
{
    struct Edge *newEdgeNode = (struct Edge *)malloc(sizeof(struct Edge));
    newEdgeNode->dest = dest;
    newEdgeNode->Length = Length;
    newEdgeNode->congestion = 0;
    strcpy(newEdgeNode->name, name);
    newEdgeNode->next = NULL;
    return newEdgeNode;
}
struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = 0;

    graph->array = (struct EdgeList *)malloc(V * sizeof(struct EdgeList)); //allocate memory of array;

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL; //sets head of each linked list in array to null

    return graph;
}
void addEdge(struct Graph *graph, int src, int dest, int Length, char *name, int type)
{
    struct Edge *newNode = newEdge(dest, Length, name); //inserting new edge in edge list of source
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    graph->E++;

    if (type == 1)
    {
        newNode = newEdge(src, Length, name);
        newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;
    }
}

void showlist(struct Graph *g)
{
    printf("number of vertices : %d | number of edges : %d\n", g->V, g->E);
    for (int i = 0; i < g->V; i++)
    {
        printf("%d :", i);
        struct Edge *e = g->array[i].head;
        while (e != NULL)
        {
            printf("(%d , %d , %d , %s ) ---> ", e->dest, e->Length, e->congestion, e->name);
            e = e->next;
        }
        printf(" x \n");
    }
}

/*returs 1 if succesfully able to update edge between src and dest
returns 0 if there is no edge between src and dest*/
int updateEdge(struct Graph *g, int src, int dest, int newCongestion)
{
    struct Edge *e = g->array[src].head;
    while (e != NULL)
    {
        if (e->dest == dest)
        {
            break;
        }
        e = e->next;
    }
    if (e == NULL)
    {
        return -1;
    }
    e->congestion = newCongestion;
}

int increaseCongestion(struct Graph *g, int src, int dest)
{
    struct Edge *e = g->array[src].head;
    while (e != NULL)
    {
        if (e->dest == dest)
        {
            break;
        }
        e = e->next;
    }
    if (e == NULL)
    {
        return -1;
    }
    e->congestion++;
}
int decreaseCongestion(struct Graph *g, int src, int dest)
{
    struct Edge *e = g->array[src].head;
    while (e != NULL)
    {
        if (e->dest == dest)
        {
            break;
        }
        e = e->next;
    }
    if (e == NULL)
    {
        return -1;
    }
    e->congestion--;
}

// int main()
// {

//     int V = 9;
//     struct Graph *graph = createGraph(V);
//     addEdge(graph, 0, 1, 4, "a");
//     addEdge(graph, 0, 7, 8, "b");
//     addEdge(graph, 1, 2, 8, "c");
//     addEdge(graph, 1, 7, 11, "d");
//     addEdge(graph, 2, 3, 7, "e");
//     addEdge(graph, 2, 8, 2, "f");
//     addEdge(graph, 2, 5, 4, "g");
//     addEdge(graph, 3, 4, 9, "h");
//     addEdge(graph, 3, 5, 14, "i");
//     addEdge(graph, 4, 5, 10, "j");
//     addEdge(graph, 5, 6, 2, "k");
//     addEdge(graph, 6, 7, 1, "l");
//     addEdge(graph, 6, 8, 6, "m");
//     addEdge(graph, 7, 8, 7, "n");

//     updateEdge(graph, 0, 1, 10);

//     showlist(graph);

//     return 0;
// }
