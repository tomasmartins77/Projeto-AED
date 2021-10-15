
#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"

#define ESQUERDA -1
#define DIREITA 1

/** \brief
 *
 * \param tab int**
 * \param lab lab_t
 * \return int
 *
 */
int menu_perguntas(int **tab, lab_t lab, int A6_x, int A6_y)
{
    switch (lab.pergunta[1])
    {
    case '1':
        return A1(tab, lab.solx, lab.soly);
        break;
    case '2':
        return A234(tab, lab, lab.solx, lab.soly);
        break;
    case '3':
        return A234(tab, lab, lab.solx, lab.soly);
        break;
    case '4':
        return A234(tab, lab, lab.solx, lab.soly);
        break;
    case '5':
        if (tab[lab.solx - 1][lab.soly - 1] < 1)
            return -1;
        else
            return A5(tab, lab);
        break;
    case '6':
        if (tab[lab.solx - 1][lab.soly - 1] != 0 || tab[A6_x - 1][A6_y - 1] != 0)
            return 0;
        else
            return A6(tab, lab, A6_x, A6_y);
        break;
    }
    exit(1);
}

/** \brief
 *
 * \param tab int**
 * \param x int
 * \param y int
 * \return int
 *
 */
int A1(int **tab, int x, int y)
{
    return tab[x - 1][y - 1];
}

/** \brief
 *
 * \param tab int**
 * \param lab lab_t
 * \param x int
 * \param y int
 * \return int
 *
 */
int A234(int **tab, lab_t lab, int x, int y)
{
    int resultado = 0, i;

    for (i = -1; i <= 1; i += 2)
    {
        if (check_if_outside(lab, x + i, y) == 0)
        {
            resultado = A1(tab, x + i, y);
            if (verifica_coord(lab, resultado) == 1)
                return 1;
        }
        if (check_if_outside(lab, x, y + i) == 0)
        {
            resultado = A1(tab, x, y + i);
            if (verifica_coord(lab, resultado) == 1)
                return 1;
        }
    }
    return 0;
}

/** \brief
 *
 * \param tab int**
 * \param lab lab_t
 * \return int
 *
 */
int A5(int **tab, lab_t lab)
{
    if (tab[lab.solx - 1][lab.soly - 1] > 0)
    {
        if (check_if_outside(lab, lab.solx - 1, lab.soly) != -2 && tab[lab.solx - 2][lab.soly - 1] == 0 && check_if_outside(lab, lab.solx + 1, lab.soly) != -2 && tab[lab.solx][lab.soly - 1] == 0)
            return 1;
        else if (check_if_outside(lab, lab.solx, lab.soly - 1) != -2 && tab[lab.solx - 1][lab.soly - 2] == 0 && check_if_outside(lab, lab.solx, lab.soly + 1) != -2 && tab[lab.solx - 1][lab.soly] == 0)
            return 1;
        else
            return 0;
    }
    return -1;
}

int A1_aux(int *tab, int x)
{
    return tab[x - 1];
}

int check_if_outside_aux(lab_t lab, int x)
{
    if (x > lab.linhas * lab.colunas || x < 0)
        return -2;
    return 0;
}

int A6_aux(int *tab, lab_t lab, int x)
{
    int resultado = 0, i;
    int variantes[4] = {1, -lab.colunas, -1, lab.colunas};

    for (i = 0; i < 4; i++)
    {
        if (check_if_outside_aux(lab, x + variantes[i]) == 0)
        {
            resultado = A1_aux(tab, x + variantes[i]);
            if (verifica_coord(lab, resultado) == 1)
                return variantes[i];
        }
    }
    return 1;
}

int *change_tab(int **tab, int *tab_id, lab_t lab)
{
    int i, j, x;
    for (i = 0, x = 0; i < lab.linhas; i++)
    {
        for (j = 0; j < lab.colunas; j++)
        {
            if (tab[i][j] == 0)
            {
                tab_id[x] = x;
            }
            else
            {
                tab_id[x] = -1;
            }
            x++;
        }
    }
    return tab_id;
}

int A6(int **tab, lab_t lab, int A6_x, int A6_y)
{
    int i = 0, aux = 0, p = 0, j = 0, q = 0, size = lab.linhas * lab.colunas, resposta = 0;

    int *tab_id = (int *)calloc(size, sizeof(int));
    int *tab_size = (int *)calloc(size, sizeof(int));
    if (tab_id == NULL || tab_size == NULL)
    {
        free_tab(tab, lab);
        exit(1);
    }

    tab_id = change_tab(tab, tab_id, lab);

    printf("penis  %d\n", tab_id[(lab.solx - 1) * lab.colunas + lab.soly - 1]);
    printf("pila   %d\n", tab_id[(A6_x - 1) * lab.colunas + A6_y - 1]);

    if (upper_coord(lab, A6_x, A6_y) == 1)
    {
        p = (lab.solx - 1) * lab.colunas + lab.soly - 1;
        q = (A6_x - 1) * lab.colunas + A6_y - 1;
    }
    else
    {
        p = (A6_x - 1) * lab.colunas + A6_y - 1;
        q = (lab.solx - 1) * lab.colunas + lab.soly - 1;
    }

    while (aux != size)
    {
        for (i = p; i != tab_id[i]; i = tab_id[i])
        {
        }
        for (j = q; j != tab_id[j]; j = tab_id[j])
        {
        }

        if (tab_size[i] < tab_size[j])
        {
            tab_id[i] = j;
            tab_size[j] += tab_size[i];
        }
        else
        {
            tab_id[j] = i;
            tab_size[i] += tab_size[j];
        }

        p += A6_aux(tab_id, lab, i);
        q += A6_aux(tab_id, lab, j);
        aux++;
    }

    if (tab_id[p] == tab_id[q])
    {
        resposta = 1;
    }

    int head;
    for (i = 0; i < size; i++)
    {
        head = 1;
        if (tab_id[i] == i)
        {
            for (j = 0; j < size; j++)
            {
                if (tab_id[j] == i)
                {
                    if (head)
                    {
                        head = 0;
                        printf("%d", j);
                    }
                    else
                        printf("-%d", j);
                }
            }
            printf("\n");
        }
    }

    free(tab_id);
    free(tab_size);
    printf("%d aeeee acertoooo", resposta);
    return resposta;
}

int upper_coord(lab_t lab, int A6_x, int A6_y)
{
    if (lab.solx < A6_x)
        return 1;
    else
        return 0;
}

/* merdas da rita que nao fazem sentido nenhum (sim, eu sei que nao faz sentido e que nao funciona):

percorrer o tabuleiro
    é branca? entao temos p
    p verifica direita
    direita é branca? entao temos par (p,q)
    direita não é branca? entao verificamos baixo
    baixo = branca

    basta terem uma coordenada em comum x ou y e serem brancas para se juntarem

    percorrer o tabuleiro todo e identificar todas as peças brancas, guardar essas coordenadas noutro tabuleiro
    número de coordenadas = id
    if (peca branca) é vizinho de outra peca branca E ESTAO DENTRO DO TABULEIRO => union


    pegar na primeira peça e




int A6(int **tab, lab_t lab, int A6_x, int A6_y)
{
    int i, j, N, p, q;
    int *id = (int *)malloc(lab.linhas * lab.colunas * sizeof(int));
    identificar todas as pecas brancas que existem no tabuleiro
    for (i = 0; i < lab.linhas; i++)
    {
        for (j = 0; j < lab.colunas; j++)
        {
            if (tab[i][j] == 0)
            se for peca branca
            {
                N++; numero total de pecas brancas
            }
        }
    }

    for (i = 0; i < N; i++)
    {
        id[i] = i;
        aquela merda do size?
    }

    {
        if ( é vizinho e esta dentro do tabuleiro)
        {
            for (i = p; i != id[i]; i = id[i])

                for (j = q; j != id[j], j = id[j])
                    ;

            if (i == j)
                continue; se tiverem a mesma raiz, ja estao ligados

            if (sz[i] < sz[j])
            {
                id[i] = j;
                sz[j] += sz[i];
            }
            else
            {
                id[j] = i;
                sz[i] += sz[j];
            }
        }
    }
}
*/
