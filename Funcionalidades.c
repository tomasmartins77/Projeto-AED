#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"

/** \brief executa os algoritmos A1-A6 consoante o que foi lido no ficheiro de entrada
 *
 * \param tab int** tabuleiro completo
 * \param lab lab_t valores importantes
 * \return int  resposta a pergunta feita
 *
 */
int menu_perguntas(int **tab, lab_t lab, int A6_x, int A6_y)
{
    switch (lab.pergunta[1]) /*verifica qual pergunta foi feita*/
    {
    case '1': /*A1*/
        return A1(tab, lab.solx, lab.soly);
        break;
    case '2': /*A2*/
        return A234(tab, lab, lab.solx, lab.soly);
        break;
    case '3': /*A3*/
        return A234(tab, lab, lab.solx, lab.soly);
        break;
    case '4': /*A4*/
        return A234(tab, lab, lab.solx, lab.soly);
        break;
    case '5': /*A5*/
        /*se nao corresponde a uma celula cinzenta*/
        if (tab[lab.solx - 1][lab.soly - 1] < 1)
            return -1;
        else
            return A5(tab, lab);
        break;
    case '6': /*A6*/
              /*se as celulas nao forem brancas*/
        if (tab[lab.solx - 1][lab.soly - 1] != 0 || tab[A6_x - 1][A6_y - 1] != 0)
            return 0;
        else
            return A6(tab, lab, A6_x, A6_y, 0, 0);
        break;
    }
    exit(1);
}

/** \brief retorna o valor de uma certa coordenada de forma a identificar o tipo de celula
 *
 * \param tab int** labirinto completo
 * \param x int coordenada que pretendemos verificar
 * \param y int
 * \return int valor da coordenada
 *
 */
int A1(int **tab, int x, int y)
{
    return tab[x - 1][y - 1];
}

/** \brief verifica quais os vizinhos de uma certa coordenada
 *
 * \param tab int** labirinto completo
 * \param lab lab_t valores importantes
 * \param x int coordenada na qual queremos verificar os vizinhos
 * \param y int
 * \return int 1 se tem os vizinhos pretendidos, 0 se nao
 *
 */
int A234(int **tab, lab_t lab, int x, int y)
{
    int resultado = 0, i;

    for (i = -1; i <= 1; i += 2) /*loop que passa apenas pelos vizinhos*/
    {
        if (check_if_outside(lab, x + i, y) == 0) /*vizinhos verticais*/
        {
            resultado = A1(tab, x + i, y);
            if (verifica_coord(lab, resultado) == 1)
                return 1;
        }
        if (check_if_outside(lab, x, y + i) == 0) /*vizinhos horizontais*/
        {
            resultado = A1(tab, x, y + i);
            if (verifica_coord(lab, resultado) == 1)
                return 1;
        }
    }
    return 0;
}

/** \brief verifica se a celula e cinzenta e quebravel
 *
 * \param tab int** labirinto completo
 * \param lab lab_t valores importantes
 * \return int 1 se e quebravel, 0 se nao, -1 se a celula nao e cinzenta
 *
 */
int A5(int **tab, lab_t lab)
{
    if (tab[lab.solx - 1][lab.soly - 1] > 0) /*verifica se a celula e cinzenta*/
    {
        /*se esta dentro do tabuleiro e se esta rodeada pelo menos duas pecas brancas disponiveis (esquerda+direita ou cima+baixo)*/
        if (check_if_outside(lab, lab.solx - 1, lab.soly) != -2 && tab[lab.solx - 2][lab.soly - 1] == 0 && check_if_outside(lab, lab.solx + 1, lab.soly) != -2 && tab[lab.solx][lab.soly - 1] == 0)
            return 1;
        else if (check_if_outside(lab, lab.solx, lab.soly - 1) != -2 && tab[lab.solx - 1][lab.soly - 2] == 0 && check_if_outside(lab, lab.solx, lab.soly + 1) != -2 && tab[lab.solx - 1][lab.soly] == 0)
            return 1;
        else
            return 0;
    }
    return -1;
}

/** \brief verifica se 2 celulas se encontram na mesma sala
 *
 * \param tab int** labirinto completo
 * \param lab lab_t struct valores importantes para a resolucao
 * \param int A6_x valor da segunda coordenada
 * \param int A6_x valor da segunda coordenada
 * \return int 1 se as celulas estao na mesma sala, 0 se nao
 *
 */
int A6(int **tab, lab_t lab, int A6_x, int A6_y, int flag, int *salas)
{
    int i = 0, j = 0, x = 0, y = 0, size = lab.linhas * lab.colunas;
    int *tab_id = (int *)malloc(size * sizeof(int)); /*alocacao o array de id*/
    if (tab_id == NULL)
    {
        free_tab(tab, lab);
        exit(1);
    }

    int *tab_size = (int *)malloc(size * sizeof(int)); /*alocacao o array de size*/
    if (tab_size == NULL)
    {
        free_tab(tab, lab);
        exit(1);
    }

    for (i = 0; i < size; i++) /*inicializacao de valores*/
    {
        tab_size[i] = 1;
        tab_id[i] = i;
    }

    for (x = 0; x < lab.linhas; x++) /*percorre todo o tabuleiro*/
    {
        for (y = 0; y < lab.colunas; y++)
        {
            if (A1(tab, x + 1, y + 1) != 0) // se for peca branca
                continue;

            for (i = x * lab.colunas + y; i != tab_id[i]; i = tab_id[i])
                ;

            if (x - 1 > 0 && tab[x - 1][y] == 0) /*vizinho de cima*/
            {
                for (j = (x - 1) * lab.colunas + y; j != tab_id[j]; j = tab_id[j])
                    ;
                conn(tab_id, tab_size, i, j, x * lab.colunas + y, (x - 1) * lab.colunas + y);
            }

            if (x + 1 < lab.linhas && tab[x + 1][y] == 0) /*vizinho de baixo*/
            {
                for (j = (x + 1) * lab.colunas + y; j != tab_id[j]; j = tab_id[j])
                    ;
                conn(tab_id, tab_size, i, j, x * lab.colunas + y, (x + 1) * lab.colunas + y);
            }

            if (y - 1 > 0 && tab[x][y - 1] == 0) /*vizinho da esquerda*/
            {
                for (j = x * lab.colunas + y - 1; j != tab_id[j]; j = tab_id[j])
                    ;
                conn(tab_id, tab_size, i, j, x * lab.colunas + y, x * lab.colunas + y - 1);
            }

            if (y + 1 < lab.colunas && tab[x][y + 1] == 0) /*vizinho da direita*/
            {
                for (j = x * lab.colunas + y + 1; j != tab_id[j]; j = tab_id[j])
                    ;
                conn(tab_id, tab_size, i, j, x * lab.colunas + y, x * lab.colunas + y + 1);
            }
        }
    }

    for (i = (A6_x - 1) * lab.colunas + A6_y - 1; i != tab_id[i]; i = tab_id[i])
        ;
    for (j = (lab.solx - 1) * lab.colunas + lab.soly - 1; j != tab_id[j]; j = tab_id[j])
        ;

    if (i == j) /*verifica se estao conectados*/
    {
        free(tab_id);
        free(tab_size);
        return 1;
    }

    if (flag == 1)
    {
        int *valores = NULL;
        int *ocurrencias = NULL;
        for (i = 0; i * lab.colunas < lab.linhas * lab.colunas; i++)
        {
            for (j = 0; j < lab.colunas; j++)
            {
                if (tab[i][j] == 0)
                {

                    if (tab_id[j + i * lab.colunas] == j + i * lab.colunas)
                        (*salas)++;
                }
            }
        }

        ocurrencias = (int *)malloc(sizeof(int) * *salas);
        if (ocurrencias == NULL)
            exit(1);

        valores = (int *)malloc(sizeof(int) * *salas);
        if (valores == NULL)
            exit(1);

        // initialize array
        for (i = 0, j = -3; i < *salas; i++, j--)
        {
            ocurrencias[i] = -1;
            valores[i] = j;
        }

        for (x = 0; x < lab.linhas; x++)
        {
            for (y = 0; y < lab.colunas; y++)
            {
                if (A1(tab, x + 1, y + 1) != 0) // se for peca branca
                    continue;

                for (j = x * lab.colunas + y; j != tab_id[j]; j = tab_id[j])
                    ;

                for (i = 0; i < *salas && ocurrencias[i] != -1 && ocurrencias[i] != tab_id[j]; i++)
                    ;

                if (ocurrencias[i] == -1)
                    ocurrencias[i] = tab_id[x * lab.colunas + y];

                tab[x][y] = valores[i];
            }
        }
        free(valores);
        free(ocurrencias);
    }
    /*for (x = 0; x < lab.linhas; x++) percorre todo o tabuleiro
    {
        for (y = 0; y < lab.colunas; y++)
        {
            printf("%3d ", tab[x][y]);
        }
        printf("\n");
    }
    */

    free(tab_id);
    free(tab_size);
    return 0;
}
