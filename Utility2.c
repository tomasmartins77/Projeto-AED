#include "Utility2.h"
#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"
#include "graphs.h"

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
 * \return o node seguinte de uma lista. retorna NULL se o node atual estiver vazio ou se nao houver node seguinte 
 *
 */
Lista *getNextNodeLista(Lista *node)
{
    return ((node == NULL) ? NULL : node->next);
}

/** \brief verifica os vizinhos horizontais e verticais de uma parede atualizando os valores de ESQ, DIR, CIM, BAI
 *
 * \param tab int** labirinto completo
 * \param lab lab_t linhas e colunas 
 * \param posx int posicao atual
 * \param posy int posicao atual
 * \param ESQ int* vizinho da esquerda
 * \param DIR int* vizinho da direita
 * \param CIM int* vizinho de cima
 * \param BAI int* vizinho de baixo
 * \return void 
 *
 */
void vizinhos(int **tab, lab_t lab, int posx, int posy, int *ESQ, int *DIR, int *CIM, int *BAI)
{
    /*se ambas as coordenadas da esquerda e da direita (vizinhos horizontais) estiverem dentro do tabuleiro e se forem salas */
    if (check_if_outside(lab, posx + 1, *ESQ + 1) == 0 && A1(tab, posx + 1, *ESQ + 1) < -2 && check_if_outside(lab, posx + 1, *DIR + 1) == 0 && A1(tab, posx + 1, *DIR + 1) < -2)
    {
        /*as coordenadas ficam com o id da sala*/
        *ESQ = A1(tab, posx + 1, *ESQ + 1);
        *DIR = A1(tab, posx + 1, *DIR + 1);
    }
    else
    {
        *ESQ = 0;
        *DIR = 0;
    }
    /*se ambas as coordenadas de cima e de baixo (vizinhos verticais )estiverem dentro do tabuleiro e se forem salas */
    if (check_if_outside(lab, *CIM + 1, posy + 1) == 0 && A1(tab, *CIM + 1, posy + 1) < -2 && check_if_outside(lab, *BAI + 1, posy + 1) == 0 && A1(tab, *BAI + 1, posy + 1) < -2)
    {
        /*as coordenadas ficam com o id da sala*/
        *CIM = A1(tab, *CIM + 1, posy + 1);
        *BAI = A1(tab, *BAI + 1, posy + 1);
    }
    else
    {
        *CIM = 0;
        *BAI = 0;
    }
}

/** \brief verifica se uma parede e quebravel no contexto dado
 *
 * \param tab int** labirinto completo
 * \param lab lab_t linhas e colunas 
 * \param x int posicao atual
 * \param y int posicao atual
 * \return int 0 se nao for quebravel, 1 se for quebravel
 *
 */
int quebravel(int **tab, lab_t lab, int x, int y)
{
    /*se for uma parede de custo superior a 0*/
    if (A1(tab, x + 1, y + 1) > 0)
    {
        /*se esta dentro do tabuleiro e se esta rodeada pelo menos duas pecas brancas disponiveis (esquerda+direita ou cima+baixo)*/
        if (check_if_outside(lab, x, y + 1) != -2 && A1(tab, x, y + 1) < -1 && check_if_outside(lab, x + 2, y + 1) != -2 && A1(tab, x + 2, y + 1) < -1)
            return 1; /*e quebravel*/
        if (check_if_outside(lab, x + 1, y) != -2 && A1(tab, x + 1, y) < -1 && check_if_outside(lab, x + 1, y + 2) != -2 && A1(tab, x + 1, y + 2) < -1)
            return 1;
    }
    return 0;
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

    if (first == NULL) /* se a lista estiver vazia*/
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

/** \brief compara dois inteiros
 *
 * \param item1 int 
 * \param item1 int 
 * \return valor menor, igual ou maior do que 0 consoante o item1 seja menor, igual ou maior que o item2, respetivamente
 *
 */
int comparisonItemFnt(int item1, int item2)
{
    if (item1 < item2)
        return -1;
    else if (item1 == item2)
        return 0;
    else
        return 1;
}

/** \brief compara o peso dois inteiros
 *
 * \param item1 int 
 * \param item1 int 
 * \param wt *int peso 
 * \return valor menor, igual ou maior do que 0 consoante o peso do item1 seja menor, igual ou maior que o peso do item2, respetivamente
 *
 */
int comparisonItemWeight(int item1, int item2, int *wt)
{
    if (wt[item1] < wt[item2])
        return -1;
    else if (wt[item1] == wt[item2])
        return 0;
    else
        return 1;
}

/** \brief conta o numero de salas e "pinta" todas as salas com o mesmo id negativo e consecutivo
 *
 * \param tab int** labirinto completo
 * \param lab lab_t linhas e colunas
 * \param tab_id int* id de cada sala
 * \param salas int** numero de salas
 * \return void
 *
 */
void verifica_salas(int **tab, lab_t lab, int *tab_id, int **salas)
{
    int count = -3, x, y, j;
    /*percorre o tabuleiro inteiro*/
    for (x = 0; x < lab.linhas; x++)
    {
        for (y = 0; y < lab.colunas; y++)
        {
            if (A1(tab, x + 1, y + 1) == 0) /*se a peca for branca*/
            {
                for (j = x * lab.colunas + y; tab_id[j] >= 0 && j != tab_id[j];)
                {
                    j = tab_id[j];
                }

                /*se o id ainda nao tiver sido alterado, estamos diante de uma sala que ainda nao foi contabilizada*/
                if (tab_id[j] >= 0)
                {
                    (**salas)++;         /*incrementar o numero de salas*/
                    tab_id[j] = count--; /*alterar o id dessa sala para id negativo e consecutivo (Ex: -3, -4, -5, ...)*/
                }
                tab[x][y] = tab_id[j]; /*"pintar" o tabuleiro*/
            }
        }
    }
    return;
}