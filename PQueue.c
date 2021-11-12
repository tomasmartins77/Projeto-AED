#include "PQueue.h"

/**
 * @brief inicializa a priority queue, o array de posicao(indica a posicao do vertice na fila)
 *        , variavel de
 *
 * @param pq fila
 * @param size numero de vertices do grafo
 * @return Queue*
 */
Queue *PQinit(Queue *pq, int size)
{
    pq = (Queue *)malloc(sizeof(Queue));
    if (pq == NULL)
        exit(1);
    pq->queue = (int *)calloc(size, sizeof(int));
    if (pq->queue == NULL)
        exit(1);
    pq->posicao = (int *)malloc(size * sizeof(int));
    if (pq->posicao == NULL)
        exit(1);

    pq->ffree = 0;

    for (int i = 0; i < size; i++)
        pq->posicao[i] = -1;
    return pq;
}

/**
 * @brief insere um vertice na priority queue na primeira posicao vazia
 * 
 * @param pq fila de prioridade
 * @param I vertice a ser inserido
 * @param wt vetor de custos para comparacoes
 * @param size numero de vertices
 * @return Queue* 
 */
Queue *PQinsert(Queue *pq, int I, int *wt, int size)
{
    if ((pq->ffree + 1) < size) /*se a fila nao tiver cheia*/
    {
        pq->queue[pq->ffree] = I;      /*insere na primeira posicao vazia o vertice*/
        pq->posicao[I] = pq->ffree;    /*posicao da fila do vertice*/
        pq = FixUp(pq, pq->ffree, wt); /*atualiza a prioridade*/
        pq->ffree++;                   /*temos mais um elemento na fila*/
    }
    return pq;
}

/**
 * @brief verifica se a fila esta vazia ou nao
 * 
 * @param pq fila
 * @return int 1 se a fila estiver vazia, 0 se nao
 */
int PQEmpty(Queue *pq)
{
    return pq->ffree == 0 ? 1 : 0;
}

/**
 * @brief altera uma certa posicao da fila para o seu valor correto de prioridade, de menos prioridade para mais
 *        prioridade, se o seu "pai" tiver um custo menor, vai trocar de posicao
 *        fazendo isto ate chegar a posicao correta
 * 
 * @param pq fila
 * @param Idx posicao da fila a ser verificada
 * @param wt vetor de custos para comparacao
 * @return Queue* 
 */
Queue *FixUp(Queue *pq, int Idx, int *wt)
{
    while (Idx > 0 && comparisonItemWeight(pq->queue[(Idx - 1) / 2], pq->queue[Idx], wt) == 1)
    {
        pq->posicao[pq->queue[(Idx - 1) / 2]] = Idx; /*atualiza as posicoes dos vertices*/
        pq->posicao[pq->queue[Idx]] = (Idx - 1) / 2;
        exch(pq->queue[Idx], pq->queue[(Idx - 1) / 2]); /*troca os elementos da fila*/

        Idx = (Idx - 1) / 2;
    }
    return pq;
}

/**
 * @brief altera uma certa posicao da fila para o seu valor correto de prioridade, de mais prioridade para menos
 *        prioridade, percorre a fila, verificando para que ramo da arvore o valor vai descer para
 *        de acordo com o seu custo
 * 
 * @param pq fila
 * @param Idx vertice a ser verificado
 * @param N ultima posicao da fila ocupada
 * @param wt vetor de custos para comparacao
 */
Queue *FixDown(Queue *pq, int Idx, int N, int *wt)
{
    int Child; /* índice de um nó descendente */
    while (2 * Idx < N - 1)
    { /* enquanto não chegar às folhas */
        Child = 2 * Idx + 1;
        /*verifica para que ramo da arvore vai*/
        if (Child < (N - 1) && comparisonItemWeight(pq->queue[Child], pq->queue[Child + 1], wt) == 1)
            Child++;
        if (comparisonItemWeight(pq->queue[Idx], pq->queue[Child], wt) == -1) /*encontra-se a posicao correta*/
            break;

        pq->posicao[pq->queue[Child]] = Idx; /*atualiza as posicoes dos vertices*/
        pq->posicao[pq->queue[Idx]] = Child;
        exch(pq->queue[Idx], pq->queue[Child]); /*troca os elementos da fila*/

        /* continua a descer a árvore */
        Idx = Child;
    }
    return pq;
}

/**
 * @brief elimina elemento de maior prioridade da lista, troca o elemento de maior prioridade com
 *        o de menor, e diminui uma posicao total da fila, retirando-o figurativamente da fila
 * 
 * @param pq fila
 * @param wt vetor de pesos para comparacoes
 * @return int elemento com maior prioridade depois de retirado da lista
 */
int PQdelmin(Queue *pq, int *wt)
{
    /* troca MENOR elemento com último da tabela e reordena com FixDown */
    pq->posicao[pq->queue[pq->ffree - 1]] = 0; /*atualiza as posicoes dos vertices*/
    pq->posicao[pq->queue[0]] = -2;
    exch(pq->queue[0], pq->queue[pq->ffree - 1]); /*troca os elementos da fila*/

    pq = FixDown(pq, 0, pq->ffree - 1, wt);
    /* ultimo elemento não considerado na reordenação */
    return pq->queue[--pq->ffree];
}

/**
 * @brief algoritmo de dijkstras
 *
 * @param G grafo completo
 * @param s sala inicial
 * @param st vetor com o caminho de menor custo
 * @param wt vetor com os pesos de onde se chega de cada aresta
 */
void Dijkstras(Graph *G, int s, int st[], int wt[])
{
    int v, w;
    Lista *t;
    Edge *edge;
    Queue *pq = NULL;
    /*inicializacao da fila, st e wt*/
    pq = PQinit(pq, G->vertex);
    for (v = 0; v < G->vertex; v++)
    {
        st[v] = -1;
        wt[v] = INT_MAX;
    }
    /*inserir o vertice para qual se quer comecar na fila*/
    pq = PQinsert(pq, s, wt, G->vertex);
    wt[s] = 0;
    while (!PQEmpty(pq) && pq->posicao[0] != -2)
    {
        v = PQdelmin(pq, wt); /*marca esse vertice como visto e guarda-o para verificar as suas arestas*/
        pq->posicao[v] = -2;  /*vertice visto*/
        if (v == 0)
            continue;
        for (t = G->adj[v]; t != NULL; t = getNextNodeLista(t)) /*percorre a lista do vertice que agora tem maior prioridade (?)*/
        {
            edge = getItemLista(t);
            if (wt[w = edge->V] > wt[v] + edge->W && wt[0] > wt[v] + edge->W)
            {
                wt[w] = wt[v] + edge->W; /*se a relaxacao de aresta for bem feita, atualiza o custo*/

                if (pq->posicao[w] == -1) /*se for a primeira vez que vai inserir esse vertice na queue*/
                    pq = PQinsert(pq, w, wt, G->vertex);
                else
                    pq = FixUp(pq, pq->posicao[w], wt); /*atualiza a prioridade*/

                st[w] = v; /*vertice de onde a aresta veio*/
            }
        }
    }
    free(pq->posicao);
    free(pq->queue);
    free(pq);
}
