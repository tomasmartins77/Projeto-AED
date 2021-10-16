
#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"

/** \brief executa os algoritmos A1-A6 consoante o que foi lido no ficheiro de entrada
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

int A6(int **tab, lab_t lab, int A6_x, int A6_y)
{
    int i = 0, j = 0, x = 0, y = 0, size = lab.linhas * lab.colunas;

    int *tab_id = (int *)malloc(size * sizeof(int));
    if (tab_id == NULL)
    {
        free_tab(tab, lab);
        exit(1);
    }

    int *tab_size = (int *)malloc(size * sizeof(int));
    if (tab_size == NULL)
    {
        free_tab(tab, lab);
        exit(1);
    }

    for (i = 0; i < size; i++)
    {
        tab_size[i] = 1;
        tab_id[i] = i;
    }

    for (x = 0; x < lab.linhas; x++)
    {
        for (y = 0; y < lab.colunas; y++)
        {
            if (tab[x][y] != 0)
                continue;

            for (i = x * lab.colunas + y; i != tab_id[i]; i = tab_id[i])
                ;

            if (x - 1 > 0 && tab[x - 1][y] == 0)
            {
                for (j = (x - 1) * lab.colunas + y; j != tab_id[j]; j = tab_id[j])
                    ;
                conn(tab_id, tab_size, i, j);
            }

            if (x + 1 < lab.linhas && tab[x + 1][y] == 0)
            {
                for (j = (x + 1) * lab.colunas + y; j != tab_id[j]; j = tab_id[j])
                    ;
                conn(tab_id, tab_size, i, j);
            }

            if (y - 1 > 0 && tab[x][y - 1] == 0)
            {
                for (j = x * lab.colunas + y - 1; j != tab_id[j]; j = tab_id[j])
                    ;
                conn(tab_id, tab_size, i, j);
            }

            if (y + 1 < lab.colunas && tab[x][y + 1] == 0)
            {
                for (j = x * lab.colunas + y + 1; j != tab_id[j]; j = tab_id[j])
                    ;
                conn(tab_id, tab_size, i, j);
            }
        }
    }
    for (i = (A6_x - 1) * lab.colunas + A6_y - 1; i != tab_id[i]; i = tab_id[i])
        ;
    for (j = (lab.solx - 1) * lab.colunas + lab.soly - 1; j != tab_id[j]; j = tab_id[j])
        ;
    if (i == j)
    {
        free(tab_id);
        free(tab_size);
        return 1;
    }

    free(tab_id);
    free(tab_size);
    return 0;
}