#include "Utility2.h"
#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"
#include "graphs.h"

Lista *initLista(void)
{
    return NULL;
}

/*cria e inicializa uma nova lista de adjacencias*/
Lista **criaLista(Graph *grafo)
{
    int i = 0;

    grafo->adj = (Lista **)malloc(grafo->vertex * sizeof(Lista *));
    if (grafo->adj == NULL)
        exit(1);

    for (i = 0; i < grafo->vertex; i++)
        grafo->adj[i] = initLista();

    return grafo->adj;
}

void freeLista(Lista *first, void (*destruir_fn)(Item))
{
    Lista *aux = first;
    Lista *next;

    for (aux = first; aux != NULL; aux = next)
    {
        next = aux->next;        /* Keep track of the next node */
        destruir_fn(aux->value); /* Free current item data with passed function */
        free(aux);               /* Free current node    */
    }
    return;
}

Lista *insertUnsortedLista(Lista *lista, Item value)
{
    /*allocate new value*/
    Lista *new = (Lista *)malloc(sizeof(Lista));
    if (new == NULL)
        exit(1);

    new->next = lista;
    new->value = value;

    return new;
}

Item getItemLista(Lista *node)
{
    if (node == NULL) /* Check that node is not empty */
        return NULL;

    return node->value;
}

Lista *getNextNodeLista(Lista *node)
{
    return ((node == NULL) ? NULL : node->next);
}

void vizinhos(int **tab, lab_t lab, int posx, int posy, int *ESQ, int *DIR, int *CIM, int *BAI)
{
    if (check_if_outside(lab, posx + 1, *ESQ + 1) == 0 && A1(tab, posx + 1, *ESQ + 1) < -2 && check_if_outside(lab, posx + 1, *DIR + 1) == 0 && A1(tab, posx + 1, *DIR + 1) < -2)
    {
        *ESQ = A1(tab, posx + 1, *ESQ + 1);
        *DIR = A1(tab, posx + 1, *DIR + 1);
    }
    else
    {
        *ESQ = 0;
        *DIR = 0;
    }
    if (check_if_outside(lab, *CIM + 1, posy + 1) == 0 && A1(tab, *CIM + 1, posy + 1) < -2 && check_if_outside(lab, *BAI + 1, posy + 1) == 0 && A1(tab, *BAI + 1, posy + 1) < -2)
    {
        *CIM = A1(tab, *CIM + 1, posy + 1);
        *BAI = A1(tab, *BAI + 1, posy + 1);
    }
    else
    {
        *CIM = 0;
        *BAI = 0;
    }
}

int quebravel(int **tab, lab_t lab, int x, int y)
{
    /*se esta dentro do tabuleiro e se esta rodeada pelo menos duas pecas brancas disponiveis (esquerda+direita ou cima+baixo)*/
    if (check_if_outside(lab, x, y + 1) != -2 && A1(tab, x, y + 1) < -1 && check_if_outside(lab, x + 2, y + 1) != -2 && A1(tab, x + 2, y + 1) < -1)
        return 1;
    if (check_if_outside(lab, x + 1, y) != -2 && A1(tab, x + 1, y) < -1 && check_if_outside(lab, x + 1, y + 2) != -2 && A1(tab, x + 1, y + 2) < -1)
        return 1;
    else
        return 0;
}