#include "modos.h"
#include "Utility.h"
#include "Utility2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph *readGraph(int salas)
{
    int i = 0;

    /*allocate graph*/
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    if (graph == NULL)
        exit(1);

    /*o numero de vertices e igual ao numero de salas*/
    graph->vertex = salas;

    /*allocate adjacency list*/
    graph->adj = (Lista **)malloc(graph->vertex * sizeof(Lista *));

    if (graph->adj == NULL)
        exit(1);

    /*criar uma lista para cada vertice*/
    for (i = 0; i < graph->vertex; i++)
    {
        graph->adj[i] = criaLista();
    }
}

void freeGraph(Graph *graph)
{
    int i = 0;
    for (i = 0; i < graph->vertex; i++)
    {
        if (graph->adj[i] != NULL)
            freeLista(graph->adj[i], free);
    }
    free(graph->adj);
    free(graph);

    return;
}