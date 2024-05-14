#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdlib.h>

typedef struct node {
    size_t vertex;
    struct node *next;
} Node;

typedef struct graph {
    size_t vertices;
    Node **adj_lists;
} Graph;

Node *create_node(size_t);
Graph *create_graph(size_t);
void add_edge(Graph*, size_t, size_t);
void print_graph(Graph*);

#endif // GRAPH_H_
