#include "Utility2.h"
#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"
#include "graphs.h"
#include "Listas.h"

/** \brief verifica os vizinhos horizontais e
 *         verticais de uma parede atualizando os valores de ESQ, DIR, CIM, BAI
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

/** \brief compara dois inteiros
 *
 * \param item1 int
 * \param item1 int
 * \return valor menor, igual ou maior do que 0 consoante o item1 seja menor,
 *         igual ou maior que o item2, respetivamente
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

/** \brief compara o peso de dois inteiros
 *
 * \param item1 int
 * \param item1 int
 * \param wt *int peso
 * \return valor menor, igual ou maior do que 0 consoante o peso do item1 seja menor,
 *         igual ou maior que o peso do item2, respetivamente
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

/**
 * @brief imprime para o ficheiro o numero de paredes partidas ou
 *        quais as paredes partidas
 *
 * @param graph grafo completo
 * @param fp_out ficheiro de saida
 * @param st vetor com o caminho de menor custo
 * @param flag 1 se quiser contar as paredes, else se imprimir quais as paredes
 */
void print_file(Graph *graph, FILE *fp_out, int *st, int flag)
{
    int paredes = 0, i = 0;
    Lista *aresta = NULL;
    Edge *edge = NULL;

    /*percorrer a search tree*/
    while (st[i] != -1)
    {
        for (aresta = graph->adj[i]; aresta != NULL; aresta = getNextNodeLista(aresta))
        {
            edge = getItemLista(aresta);
            /*se o vertice estiver na search tree*/
            if (edge->V == st[i])
            {
                if (flag == 1)
                    paredes++; /*incrementar o numero de paredes*/
                else
                    fprintf(fp_out, "%d %d %d\n", edge->x + 1, edge->y + 1, edge->W);

                i = edge->V;
                break;
            }
        }
    }
    if (flag == 1)
        fprintf(fp_out, "%d\n", paredes);
}