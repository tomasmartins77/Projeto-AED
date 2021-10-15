#include "modos.h"
#include "Utility.h"

/** \brief inicializa o tabuleiro
 *
 * \param lab lab_t
 * \return int**
 *
 */
int **init_tab(lab_t lab)
{
    int i = 0;
    int **tab = (int **)calloc(lab.linhas, sizeof(int *));

    for (i = 0; i < lab.linhas; i++)
    {
        tab[i] = (int *)calloc(lab.colunas, sizeof(int));
    }
    return tab;
}

/** \brief struct que contem os dados de cada labirinto
 *
 * \return lab_t
 *
 */
lab_t init_maze()
{
    int i = 0;
    lab_t lab;
    lab.linhas = 0;
    lab.colunas = 0;
    lab.blocos = 0;
    lab.solx = 0;
    for (i = 0; i < 2; i++)
        lab.pergunta[i] = 0;
    lab.soly = 0;
    return lab;
}

/** \brief liberta a memória alocada para todo o tabuleiro
 *
 * \param tab int**
 * \param lab lab_t
 * \return void
 *
 */
void free_tab(int **tab, lab_t lab)
{
    int i = 0;
    for (i = 0; i < lab.linhas; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

/** \brief verifica se a coordenada se encontra dentro do tabuleiro, se nao estiver retorna -2, se estiver retorna 0
 *
 * \param lab lab_t
 * \param x int
 * \param y int
 * \return int
 *
 */
int check_if_outside(lab_t lab, int x, int y)
{
    if (x > lab.linhas || y > lab.colunas || x < 1 || y < 1)
        return -2;
    return 0;
}

/** \brief
 *
 * \param filename char*
 * \param offset int
 * \return int
 *
 */
int check_filename(char *filename, int offset)
{
    int i = 0, j = 0, t = 0;
    char ex[offset + 1];
    for (i = 0; i < offset + 1; i++)
        ex[i] = '\0';

    i = strlen(filename);
    t = i - offset;
    for (j = 0; t < i; j++, t++)
    {
        ex[j] = filename[t];
    }

    if (offset == 4)
    {
        if (strcmp(".in1", ex) == 0)
            return 1;
    }
    return 0;
}

/** \brief muda a extencao do ficheiro de saida para .sol1
 *
 * \param filename char*
 * \return char*
 *
 */
char *change_ex(char *filename)
{
    int i = 0, j = 0, t = 0;
    char ex[6] = ".sol1";

    i = strlen(filename);
    t = i - 5;
    for (j = 0; t < i + 1; j++, t++)
    {
        filename[t + 1] = ex[j];
    }
    return filename;
}

/** \brief funcao que fecha ambos os ficheiros
 *
 * \param fp1 FILE*
 * \param fp2 FILE*
 * \return void
 *
 */
void close_files(FILE *fp1, FILE *fp2)
{
    fclose(fp1);
    fclose(fp2);
}

/** \brief verifica, de acordo com o algorimo A1-A6 lido do ficheiro de entrada a cor da celula de acordo com o custo de cada uma
 *
 * \param lab lab_t
 * \param custo int
 * \return int
 *
 */
int verifica_coord(lab_t lab, int custo)
{
    switch (lab.pergunta[1])
    {
    case '2':
        if (custo == 0)
            /*se for celula branca*/
            return 1;
        break;
    case '3':
        if (custo > 0)
            /*se for celula cinzenta*/
            return 1;
        break;
    case '4':
        if (custo == -1)
            /*se for celula preta*/
            return 1;
        break;
    case '6':
        if (custo == -1)
            return 1;
    }
    return 0;
}
