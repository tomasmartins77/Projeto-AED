#include "Utility.h"

/** \brief inicializa o tabuleiro
 *
 * \param lab lab_t numero de linhas e de colunas
 * \return int** tabuleiro vazio
 *
 */
int **init_tab(lab_t lab)
{
    int i = 0;
    int **tab = (int **)calloc(lab.linhas, sizeof(int *));
    if (tab == NULL)
        exit(1);

    for (i = 0; i < lab.linhas; i++)
    {
        tab[i] = (int *)calloc(lab.colunas, sizeof(int));
        if (tab[i] == NULL)
            exit(1);
    }
    return tab;
}

/** \brief coloca os valores do ficheiro no labirinto ou passa as linhas do ficheiro
 *         a frente quando os valores das coordenadas estao fora do labirinto
 *
 * \param lab lab_t numero de linhas e de colunas
 * \return int** tabuleiro cheio ou vazio
 *
 */
void fill(lab_t lab, int *aux_tamanho, FILE *fp_in, FILE *fp_out, int **tab, int flag)
{
    int aux_x = 0, aux_y = 0, aux_custo = 0;
    while ((*aux_tamanho) != lab.blocos)
    {
        if (fscanf(fp_in, "%d %d %d", &aux_x, &aux_y, &aux_custo) != 3)
        {
            close_files(fp_in, fp_out);
            exit(1);
        }
        if (flag == 1)
            tab[aux_x - 1][aux_y - 1] = aux_custo;
        (*aux_tamanho)++;
    }
}

/** \brief inicializa todos os valores da struct
 *
 * \return lab_t struct que contem os dados de cada labirinto
 *
 */
lab_t init_lab()
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
 * \param tab int** tabuleiro completo
 * \param lab lab_t linhas e colunas
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

/** \brief verifica se a coordenada se encontra dentro do tabuleiro
 *
 * \param lab lab_t linhas e colunas
 * \param x int coordenada a ser verificada
 * \param y
 * \return int se nao estiver retorna -2, se estiver retorna 0
 *
 */
int check_if_outside(lab_t lab, int x, int y)
{
    if (x > lab.linhas || y > lab.colunas || x < 1 || y < 1)
        return -2;
    return 0;
}

/** \brief verifica se o ficheiro tem a extensao correta
 *
 * \param filename char* nome do ficheiro
 * \return int 1 se tiver a extensao correta, 0 se nao
 *
 */
int check_filename(char *filename, int offset)
{
    int len = 0, j = 0, t = 0;
    char ex[offset + 1];
    for (j = 0; j < offset + 1; j++)
        ex[j] = '\0';

    len = strlen(filename);
    t = len - offset;
    for (j = 0; t < len; j++, t++)
        ex[j] = filename[t];

    if (strcmp(".in1", ex) == 0)
        return 1;
    if (strcmp(".in", ex) == 0)
        return 1;
    return 0;
}

/** \brief muda a extencao do ficheiro de saida para .sol1
 *
 * \param filename char* nome do ficheiro que vai ser alterado
 * \return char* nome com a alteracao
 *
 */
char *change_ex(char *filename, int offset)
{
    filename[strlen(filename) - offset] = '\0'; /*corta a string retirando o .in1 ou .in*/
    if (offset == 4)
        strcat(filename, ".sol1"); /*adiciona .sol1 no final da string*/
    else if (offset == 3)
        strcat(filename, ".sol"); /*adiciona .sol no final da string*/
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

/** \brief verifica, de acordo com o algorimo A2-A4 lido do ficheiro de entrada a cor da celula
 *         de acordo com o custo de cada uma
 *
 * \param lab lab_t A2-A4
 * \param custo int valor da celula
 * \return int 1 se correto, 0 se nao
 *
 */
int verifica_coord(lab_t lab, int custo)
{
    switch (lab.pergunta[1])
    {
    case '2': /*se for celula branca*/
        if (custo == 0)
            return 1;
        break;
    case '3': /*se for celula cinzenta*/
        if (custo > 0)
            return 1;
        break;
    case '4': /*se for celula preta*/
        if (custo == -1)
            return 1;
        break;
    }
    return 0;
}

/** \brief algoritmo de conectividade
 *
 * \param int *tab_id id de cada celula
 * \param int *tab_size tamanho de cada ramo
 * \return void
 *
 */
void conn(int *tab_id, int i, int j, int p, int q)
{
    int t = 0, x = 0;

    if (i == j) /*ja estao conectados*/
        return;
    /*conectar a arvore menor a maior*/
    if (p < q)
    {
        tab_id[i] = j;
        t = j;
    }
    else
    {
        tab_id[j] = i;
        t = i;
    }

    for (i = p; i != tab_id[i]; i = x)
    {
        x = tab_id[i];
        tab_id[i] = t;
    }
    for (j = q; j != tab_id[j]; j = x)
    {
        x = tab_id[j];
        tab_id[j] = t;
    }
}