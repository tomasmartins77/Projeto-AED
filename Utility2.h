#ifndef Utility2
#define Utility2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void change_tab(maze_t maze, int **tab, int *id_tab);

typedef struct _Node
{
    void *value;
    struct node *next;
} Node;

typedef struct _Lista
{
    Node *first;
    Node *last;
} Lista;

typedef struct _Graph
{
    int vertex;
    int edge;
    Lista **adj;
} Graph;

typedef struct _Edge
{
    int V;
    int W; //peso ou custo
} Edge;
#endif