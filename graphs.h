#ifndef graphs
#define graphs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utility2.h"
#include "modos.h"

/** \brief cria e preenche o grafo cujos vertices correspondem ao numero de salas
 *
 * \param salas numero total de salas
 * \param lab lab_t
 * \param tab int** labirinto completo
 * \return Graph grafo
 *
 */
Graph *readGraph(int salas, lab_t lab, int **tab);

/** \brief liberta a memoria alocada para o grafo
 *
 * \param graph Graph*
 * \return void
 *
 */
void freeGraph(Graph *graph);

/** \brief verifica se o vertice ja se encontra na lista
 *
 * \param first Lista* primeiro elemento da lista
 * \param value int
 * \return int 1 se estiver na lista, caso contrario 0
 *
 */
int verifica_vertice(Lista *first, int value);

/** \brief coloca os vertices nas listas de adjacencias respetivas
 *
 * \param graph Graph* grafo
 * \param tab int** labirinto completo
 * \param a int
 * \param b int
 * \param x int posicao x
 * \param y int posicao x
 * \return void
 *
 */
void put_vertice(Graph *graph, int **tab, int a, int b, int x, int y);

/** \brief troca o valor de uma aresta se o seu peso for inferior 
 *
 * \param first Lista* primeiro elemento da lista
 * \param aresta int 
 * \param value int
 * \param x int posicao x
 * \param y int posicao x
 * \return void
 *
 */
void troca_value(Lista *first, int aresta, int value, int x, int y);

#endif