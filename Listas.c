#include "Listas.h"

/** \brief inicializa uma lista a NULL
 *
 */
Lista *initLista(void)
{
    return NULL;
}

/** \brief cria e inicializa uma nova lista de adjacencias
 *
 * \param grafo Graph* grafo
 * \return Lista de adjacencias
 *
 */
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

/** \brief liberta a memoria alocada para a lista
 *
 * \param first  Lista* primeiro elemento da lista
 * \return void
 *
 */
void freeLista(Lista *first, void (*destruir_fn)(Item))
{
    Lista *aux = first;
    Lista *next;

    /*percorrer a lista ate ao final*/
    for (aux = first; aux != NULL; aux = next)
    {
        next = aux->next;
        destruir_fn(aux->value); /* liberta dados do valor atual */
        free(aux);               /* liberta node    */
    }
    return;
}

/** \brief retorna o item (valor) de um certo node nessa lista
 *
 * \param node  Lista* node de uma lista
 * \return Item (valor) de um node
 *
 */
Item getItemLista(Lista *node)
{
    if (node == NULL) /* se o node estiver vazio */
        return NULL;

    return node->value;
}

/** \brief retorna o node seguinte de uma lista
 *
 * \param node  Lista* node atual de uma lista
 * \return o node seguinte de uma lista. retorna NULL se o node atual estiver vazio ou 
 *         se nao houver node seguinte
 */
Lista *getNextNodeLista(Lista *node)
{
    return ((node == NULL) ? NULL : node->next);
}

/** \brief insere um node ordenadamente numa lista
 *
 * \param first Lista* primeiro node da lista
 * \param item Edge* aresta
 * \return
 *
 */
Lista *insertSortedLista(Lista *first, Edge *item, int (*compareItems)(int it1, int it2))
{
    Lista *new, *aux;
    Edge *edge;
    /* alocacao de memoria */
    new = (Lista *)malloc(sizeof(Lista));
    if (new == NULL)
        return NULL;

    new->value = item; /* inicializar um novo node  */
    new->next = NULL;

    if (first == NULL) /* se a lista estiver vazia */
    {
        return new;
    }
    /* lista nao esta vazia, insertion sort */
    /* inserir no inicio da lista */
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
            if (compareItems(item->V, edge->V) <= 0)/*item ordenado*/
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