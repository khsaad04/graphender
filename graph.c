#define GRAPH_IMPLEMENTATION
#include "graph.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Node *create_node(size_t v)
{
    Node *node = malloc(sizeof(Node));
    node->vertex = v;
    node->next = NULL;
    return node;
}

Graph *create_graph(size_t vs)
{
    Graph *graph = malloc(sizeof(Graph));
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
    Graph *graph = create_graph(10);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 3);
    add_edge(graph, 0, 5);

    print_graph(graph);
    return graph;
}

void draw_nodes(Graph *graph)
{
    for (size_t v = 0; v < graph->vertices; v++) {
        struct node *temp = graph->adj_lists[v];
        int font_size = 20;
        if (temp != NULL) {
            int pos_x = GetScreenWidth() / 2 - 40 * v;
            int pos_y = GetScreenHeight() / 2 - 40 * v;
            const char *text = TextFormat("%zu", v);
            DrawCircle(pos_x, pos_y, 20, RAYWHITE);
            DrawText(text, pos_x - MeasureText(text, font_size) / 2,
                     pos_y - font_size / 2, font_size, BLACK);
        }
        while (temp) {
            {
                int pos_x = GetScreenWidth() / 2 + 40 * temp->vertex;
                int pos_y = GetScreenHeight() / 2 + 40 * temp->vertex;
                const char *text = TextFormat("%zu", temp->vertex);
                DrawCircle(pos_x, pos_y, 20, RED);
                DrawText(text, pos_x - MeasureText(text, font_size) / 2,
                         pos_y - font_size / 2, font_size, BLACK);
            }
            temp = temp->next;
        }
    }
}

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
    init_raylib(graph);
    return 0;
}
