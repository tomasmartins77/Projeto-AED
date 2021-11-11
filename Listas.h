#ifndef Listas
#define Listas

#include "Utility2.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** \brief inicializa uma lista a NULL
 *
 */
Lista *initLista(void);

/** \brief cria e inicializa uma nova lista de adjacencias
 *
 */
Lista **criaLista(Graph *grafo);

/** \brief liberta a memoria alocada para a lista
 *
 */
void freeLista(Lista *lista, void(destruir_fn)(Item));

/** \brief retorna o node seguinte de uma lista
 *
 */
Lista *getNextNodeLista(Lista *node);

/** \brief retorna o item (valor) de um certo node nessa lista
 *
 */
Item getItemLista(Lista *node);

/** \brief insere um node ordenadamente numa lista
 *
 */
Lista *insertSortedLista(Lista *first, Edge *item, int (*compareItems)(int it1, int it2));

#endif