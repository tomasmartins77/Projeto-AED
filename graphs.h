#ifndef graphs
#define graphs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utility2.h"
#include "modos.h"

Graph *readGraph(int salas, lab_t lab, int **tab);

void freeGraph(Graph *graph);

void print_grafo(FILE *fp_out, Graph *graph);

int verifica_vertice(Lista *first, int value);

void troca_value(Lista *first, int aresta, int value);

void put_vertice(Graph *graph, int **tab, int a, int b, int x, int y);

#endif