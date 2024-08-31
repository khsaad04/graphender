#include <math.h>
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
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 0, 3);
    add_edge(graph, 0, 4);
    add_edge(graph, 0, 5);
    add_edge(graph, 0, 6);
    add_edge(graph, 1, 4);
    add_edge(graph, 1, 5);
    add_edge(graph, 1, 6);

    return graph;
}

void draw_nodes(Graph *graph)
{
    float angle = 360.0 / graph->vertices * PI / 180;
    float len = GetScreenHeight() / 3.0;
    float radius = len / graph->vertices;
    float font_size = radius;

    for (size_t v = 0; v < graph->vertices; v++) {
        Vector2 pos = {GetScreenWidth() / 2.0 + len * sinf(angle * v),
                       GetScreenHeight() / 2.0 - len * cosf(angle * v)};
        const char *text = TextFormat("%zu", v);
        struct node *temp = graph->adj_lists[v];
        while (temp) {
            Vector2 end_pos = {
                GetScreenWidth() / 2.0 + len * sinf(angle * temp->vertex),
                GetScreenHeight() / 2.0 - len * cosf(angle * temp->vertex)};
            DrawLineV(pos, end_pos, RED);
            temp = temp->next;
        }
        DrawCircleV(pos, len / graph->vertices, RAYWHITE);
        DrawText(text, pos.x - MeasureText(text, font_size) / 2.0,
                 pos.y - font_size / 2.0, font_size, BLACK);
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
