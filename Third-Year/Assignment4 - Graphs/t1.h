#ifndef T1_H_
#define T1_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
}Node;

// Define a structure for the adjacency list
typedef struct Graph {
    int numVertices;
    struct Node** adjList;
    int* visited;
}Graph;

Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to); // adds a directed edge
void bfs(Graph* g, int origin); //implements breath first search and prints the results
void dfs(Graph* g, int origin); //implements depth first search and prints the results
void delete_graph(Graph* g); // delete the graph and all its data structures.

#endif
