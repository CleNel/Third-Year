#include "t1.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to create a new node with a given vertex
struct Node* create_node(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
struct Graph* create_graph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjList = (struct Node**)malloc(numVertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; ++i) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void add_edge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = create_node(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Add edge from dest to src (since the graph is undirected)
    newNode = create_node(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to perform breadth-first search on a graph
void bfs(struct Graph* graph, int startVertex) {
    // Create a queue for BFS
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = -1, rear = -1;

    // Mark the current node as visited and enqueue it
    graph->visited[startVertex] = 1;
    queue[++rear] = startVertex;

    while (front != rear) {
        // Dequeue a vertex from the queue
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex
        struct Node* temp = graph->adjList[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;

            // If the adjacent vertex is not visited, mark it as visited and enqueue it
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                queue[++rear] = adjVertex;
            }

            temp = temp->next;
        }
    }

    free(queue);
}

// Function to free the memory allocated for the graph
void delete_graph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        struct Node* temp = graph->adjList[i];
        while (temp != NULL) {
            struct Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }

    free(graph->adjList);
    free(graph->visited);
    free(graph);
}
