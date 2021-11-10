#include "graphs.h"
#include "modos.h"
#include "Utility.h"
#include "Utility2.h"
#include "Funcionalidades.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph *readGraph(int salas, lab_t lab, int **tab)
{
    int x = 0, y = 0, BAI = 0, CIM = 0, ESQ = 0, DIR = 0;

    /*allocate graph*/
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL)
        exit(1);

    /*o numero de vertices e igual ao numero de salas*/
    graph->vertex = salas;

    /*criar uma lista para cada vertice*/
    graph->adj = criaLista(graph);

    for (x = 0; x < lab.linhas; x++)
    {
        for (y = 0; y < lab.colunas; y++)
        {
            if (quebravel(tab, lab, x, y) == 0)
                continue;

            ESQ = y - 1;
            DIR = y + 1;
            CIM = x - 1;
            BAI = x + 1;

            vizinhos(tab, lab, x, y, &ESQ, &DIR, &CIM, &BAI);

            put_vertice(graph, tab, ESQ, DIR, x, y);
            put_vertice(graph, tab, CIM, BAI, x, y);
        }
        if (x >= 2)
            free(tab[x - 2]);
    }
    free(tab[x - 2]);
    free(tab[x - 1]);
    free(tab);
    return graph;
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

int verifica_vertice(Lista *first, int value)
{
    Lista *aux = first;
    Edge *edge;

    while (aux != NULL)
    {
        edge = getItemLista(aux);
        if (edge->V == value)
            return 1;

        aux = aux->next;
    }
    return 0;
}

void troca_value(Lista *first, int aresta, int value, int x, int y)
{
    Lista *aux = first;
    Edge *edge;

    while (aux != NULL)
    {
        edge = (Edge *)getItemLista(aux);
        if (edge->V == aresta)
        {
            if (edge->W > value)
            {
                edge->W = value;
                edge->x = x;
                edge->y = y;
                return;
            }
        }
        aux = aux->next;
    }
    return;
}

void put_vertice(Graph *graph, int **tab, int a, int b, int x, int y)
{
    Edge *edge;
    if (a != 0 && b != 0)
    {
        if (verifica_vertice(graph->adj[-a - 3], -b - 3) == 0 && verifica_vertice(graph->adj[-b - 3], -a - 3) == 0)
        {
            edge = (Edge *)malloc(sizeof(Edge));
            if (edge == NULL)
                exit(3);

            edge->V = -b - 3;
            edge->W = tab[x][y];
            edge->x = x;
            edge->y = y;
            graph->adj[-a - 3] = insertSortedLista(graph->adj[-a - 3], edge, comparisonItemFnt);

            /* Allocates new v2 edge */
            edge = (Edge *)malloc(sizeof(Edge));
            if (edge == NULL)
                exit(3);

            edge->V = -a - 3;
            edge->W = tab[x][y];
            edge->x = x;
            edge->y = y;
            graph->adj[-b - 3] = insertSortedLista(graph->adj[-b - 3], edge, comparisonItemFnt);
        }
        else
        {
            troca_value(graph->adj[-a - 3], -b - 3, tab[x][y], x, y);
            troca_value(graph->adj[-b - 3], -a - 3, tab[x][y], x, y);
        }
    }
}