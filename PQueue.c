#include "PQueue.h"

static int *queue;/*fila de prioridade*/
static int ffree;/*primeira posicao vazia*/
static int qsize;/*tamanho total da fila*/
static int *posicao;/*posicao do vertice na fila*/

/**
 * @brief inicializa a priority queue
 *
 * @param size numero de vertices do grafo
 */
void PQinit(int size)
{
    queue = (int *)calloc(size, sizeof(int));
    if (queue == NULL)
        exit(1);
    posicao = (int *)malloc(size * sizeof(int));
    if (posicao == NULL)
        exit(1);

    qsize = size;
    ffree = 0;

    for (int i = 0; i < size; i++)
        posicao[i] = -1;
}

/**
 * @brief insere um vertice na priority queue
 *
 * @param I vertice a ser inserido
 * @param wt vetor de custos para comparacoes
 */
void PQinsert(int I, int *wt)
{
    if ((ffree + 1) < qsize)/*se a fila nao tiver cheia*/
    {
        queue[ffree] = I;/*insere na primeira posicao vazia o vertice*/
        posicao[I] = ffree;/*posicao da fila do vertice*/
        FixUp(ffree, wt);/*atualiza a prioridade*/
        ffree++;/*temos mais um elemento na fila*/
    }
}

/**
 * @brief verifica se a fila esta vazia ou nao
 *
 * @return int 1 se a fila estiver vazia, 0 se nao
 */
int PQEmpty()
{
    return ffree == 0 ? 1 : 0;
}

/**
 * @brief altera uma certa posicao da fila para o seu valor correto de prioridade, de menos prioridade para mais
 *        prioridade
 *
 * @param Idx posicao da fila a ser verificada
 * @param wt vetor de custos para comparacao
 */
void FixUp(int Idx, int *wt)
{
    while (Idx > 0 && comparisonItemWeight(queue[(Idx - 1) / 2], queue[Idx], wt) == 1)
    {
        posicao[queue[(Idx - 1) / 2]] = Idx;/*atualiza as posicoes dos vertices*/
        posicao[queue[Idx]] = (Idx - 1) / 2;
        exch(queue[Idx], queue[(Idx - 1) / 2]);/*troca os elementos da fila*/

        Idx = (Idx - 1) / 2;
    }
}

/**
 * @brief altera uma certa posicao da fila para o seu valor correto de prioridade, de mais prioridade para menos
 *        prioridade
 *
 * @param Idx vertice a ser verificado
 * @param N ultima posicao da fila ocupada
 * @param wt vetor de custos para comparacao
 */
void FixDown(int Idx, int N, int *wt)
{
    int Child; /* índice de um nó descendente */
    while (2 * Idx < N - 1)
    { /* enquanto não chegar às folhas */
        Child = 2 * Idx + 1;
        /*verifica para que ramo da arvore vai*/
        if (Child < (N - 1) && comparisonItemWeight(queue[Child], queue[Child + 1], wt) == 1)
            Child++;
        if (comparisonItemWeight(queue[Idx], queue[Child], wt) == -1) /*encontra-se a posicao correta*/
            break;

        posicao[queue[Child]] = Idx;/*atualiza as posicoes dos vertices*/
        posicao[queue[Idx]] = Child;
        exch(queue[Idx], queue[Child]);/*troca os elementos da fila*/

        /* continua a descer a árvore */
        Idx = Child;
    }
}

/**
 * @brief elimina elemento de maior prioridade da lista
 *
 * @param wt vetor de pesos para comparacoes
 * @return int elemento com maior prioridade depois de retirado da lista
 */
int PQdelmin(int *wt)
{
    /* troca MENOR elemento com último da tabela e reordena com FixDown */
    posicao[queue[ffree - 1]] = 0;/*atualiza as posicoes dos vertices*/
    posicao[queue[0]] = -2;
    exch(queue[0], queue[ffree - 1]);/*troca os elementos da fila*/

    FixDown(0, ffree - 1, wt);
    /* ultimo elemento não considerado na reordenação */
    return queue[--ffree];
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
    /*inicializacao da fila, st e wt*/
    PQinit(G->vertex);
    for (v = 0; v < G->vertex; v++)
    {
        st[v] = -1;
        wt[v] = INT_MAX;
    }
    /*inserir o vertice para qual se quer comecar na fila*/
    PQinsert(s, wt);
    wt[s] = 0;
    while (!PQEmpty() && posicao[0] != -2)
    {
        v = PQdelmin(wt); /*marca esse vertice como visto e guarda-o para verificar as suas arestas*/
        posicao[v] = -2;  /*vertice visto*/
        if (v == 0)
            continue;
        for (t = G->adj[v]; t != NULL; t = getNextNodeLista(t)) /*percorre a lista do vertice que agora tem maior prioridade (?)*/
        {
            edge = getItemLista(t);
            if (wt[w = edge->V] > wt[v] + edge->W && wt[0] > wt[v] + edge->W)
            {
                wt[w] = wt[v] + edge->W; /*se a relaxacao de aresta for bem feita, atualiza o custo*/

                if (posicao[w] == -1) /*se for a primeira vez que vai inserir esse vertice na queue*/
                    PQinsert(w, wt);
                else
                    FixUp(posicao[w], wt); /*atualiza a prioridade*/

                st[w] = v; /*vertice de onde a aresta veio*/
            }
        }
    }
    free(posicao);
    free(queue);
} 
