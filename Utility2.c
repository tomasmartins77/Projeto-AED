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
    if (A1(tab, x + 1, y + 1) > 0)
    {
        /*se esta dentro do tabuleiro e se esta rodeada pelo menos duas pecas brancas disponiveis (esquerda+direita ou cima+baixo)*/
        if (check_if_outside(lab, x, y + 1) != -2 && A1(tab, x, y + 1) < -1 && check_if_outside(lab, x + 2, y + 1) != -2 && A1(tab, x + 2, y + 1) < -1)
            return 1;
        if (check_if_outside(lab, x + 1, y) != -2 && A1(tab, x + 1, y) < -1 && check_if_outside(lab, x + 1, y + 2) != -2 && A1(tab, x + 1, y + 2) < -1)
            return 1;
    }
    return 0;
}

Lista *insertSortedLista(Lista *first, Edge *item, int (*compareItems)(int it1, int it2))
{
    Lista *new, *aux;
    Edge *edge;
    /* alloc and check */
    new = (Lista *)malloc(sizeof(Lista));
    if (new == NULL)
        return NULL;

    new->value = item; /* Initialize new node  */
    new->next = NULL;

    if (first == NULL) /* first item in list */
    {
        return new;
    }
    /* list not empty, insertion sort */
    /* insert at head */
    edge = getItemLista(first);
    if ((compareItems(item->V, edge->V) <= 0))
    {
        new->next = first;
        return new;
    }
    /* second etc */
    aux = first;
    while (aux != NULL)
    {
        if (aux->next != NULL)
        {
            edge = getItemLista(aux->next);
            if (compareItems(item->V, edge->V) <= 0)
            {
                new->next = aux->next;
                aux->next = new;
                return first;
            }
        }
        else /* none left, insert in tail */
        {
            aux->next = new;
            return first;
        }
        aux = aux->next;
    }
    return NULL;
}

int comparisonItemFnt(int item1, int item2)
{
    if (item1 < item2)
        return -1;
    else if (item1 == item2)
        return 0;
    else
        return 1;
}

int comparisonItemWeight(int item1, int item2, int *wt)
{
    if (wt[item1] < wt[item2])
        return -1;
    else if (wt[item1] == wt[item2])
        return 0;
    else
        return 1;
}

void verifica_salas(int **tab, lab_t lab, int *tab_id, int **salas)
{
    int count = -3, x, y, j;
    for (x = 0; x < lab.linhas; x++)
    {
        for (y = 0; y < lab.colunas; y++)
        {
            if (A1(tab, x + 1, y + 1) == 0) // se for peca branca
            {
                for (j = x * lab.colunas + y; tab_id[j] >= 0 && j != tab_id[j];)
                {
                    j = tab_id[j];
                }

                if (tab_id[j] >= 0)
                {
                    (**salas)++;
                    tab_id[j] = count--;
                }
                tab[x][y] = tab_id[j];
            }
        }
    }
    return;
}