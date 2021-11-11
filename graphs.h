#ifndef graphs
#define graphs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utility2.h"
#include "modos.h"

/** \brief cria e preenche o grafo cujos vertices correspondem ao numero de salas
 *
 */
Graph *readGraph(int salas, lab_t lab, int **tab);

/** \brief liberta a memoria alocada para o grafo
 *
 */
void freeGraph(Graph *graph);

/** \brief verifica se o vertice ja se encontra na lista
 *
 */
int verifica_vertice(Lista *first, int value);

/** \brief coloca os vertices nas listas de adjacencias respetivas
 *
 */
void put_vertice(Graph *graph, int **tab, int a, int b, int x, int y);

/** \brief troca o valor de uma aresta se o seu peso for inferior
 *
 */
void troca_value(Lista *first, int aresta, int value, int x, int y);

#endif