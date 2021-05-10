#ifndef _GRAPH_H_
#define _GRAPH_H_

struct Edge //structure for storing information about each street
{
    int dest;          //destination node
    int Length;        //length  of the edge
    int congestion;    //congestion on the edge at a given time i.r the number of cars
    char name[31];     //name of the street
    struct Edge *next; //pointer to the next edge of source
};

struct EdgeList //an linked list of edges
{
    struct Edge *head;
};

struct Graph //Graph datatype
{
    int V;                  //number of vertices
    int E;                  //number of edges
    struct EdgeList *array; //an array of Edgelist
};

//creates a new graph and returns its pointer
struct Graph *createGraph(int V);

//adds edge between src and dest vertex in given graph
void addEdge(struct Graph *graph, int src, int dest, int Length, char *name, int type);

void showlist(struct Graph *g);

/*returs 1 if succesfully able to update edge between src and dest
returns 0 if there is no edge between src and dest*/
int updateEdge(struct Graph *g, int src, int dest, int newCongestion);

int updateLength(struct Graph*g,int src,int dest,int newLength);

int updateName(struct Graph *g, int src, int dest, char *newName);

int deleteEdge(struct Graph *g, int src, int dest);

int increaseCongestion(struct Graph *g, int src, int dest);

int decreaseCongestion(struct Graph *g, int src, int dest);

void saveGraph(struct Graph*g,char*name);

#endif