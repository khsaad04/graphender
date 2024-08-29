#include <raylib.h>
#include <stdio.h>

#include "graph.h"

Node *create_node(size_t v)
{
    Node *node = malloc(sizeof(*node));
    node->vertex = v;
    node->next = NULL;
    return node;
}

Graph *create_graph(size_t vs)
{
    Graph *graph = malloc(sizeof(*graph));
    graph->vertices = vs;
    graph->adj_lists = malloc(vs * sizeof(Node *));
    for (size_t i = 0; i < vs; ++i) {
        graph->adj_lists[i] = NULL;
    }
    return graph;
}

void add_edge(Graph *graph, size_t from, size_t to)
{
    Node *node = create_node(to);
    node->next = graph->adj_lists[from];
    graph->adj_lists[from] = node;
}

void print_graph(Graph *graph)
{
    for (size_t v = 0; v < graph->vertices; v++) {
        struct node *temp = graph->adj_lists[v];
        printf("Node[%zu]: ", v);
        while (temp) {
            printf("-> %zu ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

Graph *init_graph(void)
{
    size_t vs = 10;
    Graph *graph = create_graph(vs);
    for (size_t i = 0; i < vs; ++i) {
        for (size_t j = 0; j < vs; ++j) {
            add_edge(graph, i, j);
        }
    }

    print_graph(graph);
    return graph;
}
void draw_nodes(Graph *graph) { /*TODO */ }

void init_raylib(Graph *graph)
{
    InitWindow(800, 600, "Graph Representation");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        draw_nodes(graph);
        EndDrawing();
    }
    CloseWindow();
}

int main(void)
{
    Graph *graph = init_graph();
    /*init_raylib(graph);*/
    return 0;
}
