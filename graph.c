#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

//creates and returns pointer a new edge with given dest , length and name
struct Edge *newEdge(int dest, int Length, char *name)
{
    struct Edge *newEdgeNode = (struct Edge *)malloc(sizeof(struct Edge));
    newEdgeNode->dest = dest;
    newEdgeNode->Length = Length;
    newEdgeNode->congestion = 0;
    strcpy(newEdgeNode->name, name);
    newEdgeNode->next = NULL;
    return newEdgeNode;
}

//creates and returns a pointer to the graph with V number of vertices
struct Graph *createGraph(int V)
{
    //allocating memory to it
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));

    //initilizing number of vertices in graph
    graph->V = V;
    //initilizing number of edges in graph to zero since no edge is present in staring
    graph->E = 0;

    //allocating memory for adjancy list of graph
    graph->array = (struct EdgeList *)malloc(V * sizeof(struct EdgeList)); //allocate memory of array;

    //initilizing values of adjancany list to all null since no edges are present in starting
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL; //sets head of each linked list in array to null

    //returning the pointer to the created memory location
    return graph;
}

//adds edge in the given graph between src and dest vertex with edge_Length=Length , edge_Name=name
//if type is 0 a directed edge is added in graph
//if type is 1 a non-directed edge is added in graph
void addEdge(struct Graph *graph, int src, int dest, int Length, char *name, int type)
{
    //allocating memory for new edge by calling newEdge function
    struct Edge *newNode = newEdge(dest, Length, name); //inserting new edge in edge list of source

    //adding edge between src and dest
    //adding the current edge at the starting of the adjancacy list of src
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    //increamenting the count of edges in graph
    graph->E++;

    //if type is 1 adding another edge in between dest and src also
    if (type == 1)
    {
        //allocating memory for new edge by calling newEdge function
        newNode = newEdge(src, Length, name);
        //adding the current edge at the starting of the adjancacy list of src
        newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;
        //increamenting the count of edges in graph
        graph->E++;
    }
}

//a function to print adjancacy list of all the edges in the graph
void showlist(struct Graph *g)
{
    printf("number of vertices : %d | number of edges : %d\n", g->V, g->E);
    //traversing through all the vertices
    for (int i = 0; i < g->V; i++)
    {
        //printing ID of vertex
        printf("%d :", i);

        //traversing through the adjacancy list of src
        struct Edge *e = g->array[i].head;
        while (e != NULL)
        {
            //printing that edge data
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
    //traversing through the adjacancy list of the src node
    struct Edge *e = g->array[src].head;
    //traversing through until current node is not equals to null or dest is found
    while (e != NULL)
    {
        //breaking if dest is found
        if (e->dest == dest)
        {
            break;
        }
        //traversing
        e = e->next;
    }
    //e will be null if there is no edge between src and dest
    if (e == NULL)
    {
        //returning -1
        return -1;
    }
    //updating congestion
    e->congestion = newCongestion;
}

//a function to increase congestion of the node
int increaseCongestion(struct Graph *g, int src, int dest)
{
    //traversing through the adjacancy list of the src node
    struct Edge *e = g->array[src].head;
    //traversing through until current node is not equals to null or dest is found
    while (e != NULL)
    {
        //breaking if dest is found
        if (e->dest == dest)
        {
            break;
        }
        e = e->next;
    }
    //e will be null if there is no edge between src and dest
    if (e == NULL)
    {
        //returning -1
        return -1;
    }
    //increamenting congestion
    e->congestion++;
}
//a function to decrease congestion of given src and node
int decreaseCongestion(struct Graph *g, int src, int dest)
{
    //traversing through the adjacancy list of the src node
    struct Edge *e = g->array[src].head;
    //traversing through until current node is not equals to null or dest is found
    while (e != NULL)
    {
        //breaking if dest is found
        if (e->dest == dest)
        {
            break;
        }
        e = e->next;
    }
    //e will be null if there is no edge between src and dest
    if (e == NULL)
    {
        //returning -1
        return -1;
    }
    //decrementing congestion
    e->congestion--;
}

// a function to store the graph in txt formate with given name
//in data folder
void saveGraph(struct Graph *g, char *name)
{
    //path of saving location
    char path[100] = ".\\data\\";
    //complete name of file with path appended
    char c_name[100];
    //extension of the saved file
    char ext[6] = ".txt";

    //appending name to ext
    strcpy(c_name, name);
    strcat(c_name, ext);

    //appending name with path
    strcat(path, c_name);

    //opening filepointer with give name
    FILE *f = fopen(path, "w");

    //writing number of vertices and edges of graph in the file
    fprintf(f, "%d %d\n", g->V, g->E);

    //writing edge list of each vertex of graph in file
    for (int i = 0; i < g->V; i++)
    {
        //traversing through the adjlist of i
        struct Edge *curr = g->array[i].head;
        while (curr != NULL)
        {
            //writing current vertex ,destination vertex, nameof vertex and length of vertex
            fprintf(f, "%d %d %s %d\n", i, curr->dest, curr->name, curr->Length);
            //traversing
            curr = curr->next;
        }
    }
    //closing the opened filepointer
    fclose(f);
}

//updates the length of given edge
int updateLength(struct Graph *g, int src, int dest, int newLength)
{
    //traversing through the adjlist of src vertex while end is not reached
    struct Edge *e = g->array[src].head;
    while (e != NULL)
    {
        //if dest is reached break
        if (e->dest == dest)
        {
            break;
        }
        e = e->next;
    }
    //if e is null that means there is no edge between src and dest
    if (e == NULL)
    {
        return -1;
    }
    //updating the length of edge
    e->Length = newLength;
}

//updates the name of given edge
int updateName(struct Graph *g, int src, int dest, char *newName)
{
    //traversing throught adjancacy list of src node
    struct Edge *e = g->array[src].head;
    //traversing till end is reached
    while (e != NULL)
    {
        //if dest is found break
        if (e->dest == dest)
        {
            break;
        }
        e = e->next;
    }
    //if e is null that means there is no edge between src and dest
    if (e == NULL)
    {
        return -1;
    }
    //updateing name of edge 
    strcpy(e->name, newName);
}

//deletes edge from a given graph
int deleteEdge(struct Graph *g, int src, int dest)
{
    //taversing through the list of current src node
    struct Edge *e = g->array[src].head, *prev;
    struct Edge *curr = g->array[src].head;
    //if(e == NULL) that means there is no edges from the given src
    if (e == NULL)
    {
        return 0;
    }
    //if dest is reached directlty changed the head of adj list of src and freed the deleted node 
    if (e->dest == dest)
    {
        struct Edge *temp = e;
        g->array[src].head = e->next;
        free(temp);
        return 1;
    }

    //traversing till we do not find the destinaition node or till end of list
    while (e != NULL && e->dest != dest)
    {
        prev = e;
        e = e->next;
    }
    //if e == null there is no edge between the src and destinaiton 
    if (e == NULL)
    {
        return 0;
    }

    //else update the next of previous node to the deleted node with next node of deleting node
    prev->next = e->next;
    //deleting dest node
    free(e);
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
