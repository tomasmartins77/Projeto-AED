#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"
#include "graphs.h"
#include "Utility2.h"
#include "PQueue.h"

/** \brief realiza o modo da fase intermedia
 *
 * \param fp_in FILE* ficheiro de entrada
 * \param fp_out FILE* ficheiro de saida
 * \return void
 *
 */
void modo1(FILE *fp_in, FILE *fp_out)
{
    lab_t lab = init_lab(); /*inicializa a struct que vai receber os valores dos ficheiros*/
    int aux_tamanho = 0, resposta = 0, sec_cordx = 0, sec_cordy = 0;
    int **tab = NULL;

    while (fp_in != NULL)
    {
        if (fscanf(fp_in, "%d %d %d %d %s", &lab.linhas, &lab.colunas, &lab.solx, &lab.soly, lab.pergunta) != 5)
            break;

        if (lab.pergunta[1] == '6') /*se for o A6*/
        {
            if (fscanf(fp_in, "%d %d %d", &sec_cordx, &sec_cordy, &lab.blocos) != 3)
                break;

            if (check_if_outside(lab, lab.solx, lab.soly) == -2 || check_if_outside(lab, sec_cordx, sec_cordy) == -2)
                fill(lab, &aux_tamanho, fp_in, fp_out, tab, 0); /*se as coordenadas lidas estiverem fora do labirinto*/

            else
                tab = init_tab(lab); /*se estiver tudo bem*/
        }
        else /*se nao for o A6*/
        {
            if (fscanf(fp_in, "%d", &lab.blocos) != 1)
                break;
            /*se as coordenadas lidas estiverem fora do labirinto*/
            if (check_if_outside(lab, lab.solx, lab.soly) == -2)
                fill(lab, &aux_tamanho, fp_in, fp_out, tab, 0);
            /*se estiver tudo bem*/
            else
                tab = init_tab(lab);
        }
        /*resto do labirinto*/
        if (aux_tamanho != lab.blocos)
        {
            fill(lab, &aux_tamanho, fp_in, fp_out, tab, 1);
        }
        /*se estiver fora, a resposta e -2*/
        if (check_if_outside(lab, lab.solx, lab.soly) == -2 || (lab.pergunta[1] == '6' && check_if_outside(lab, sec_cordx, sec_cordy) == -2))
            resposta = -2;
        else
        {
            resposta = menu_perguntas(tab, lab, sec_cordx, sec_cordy);
            free_tab(tab, lab);
        }
        aux_tamanho = 0;
        fprintf(fp_out, "%d\n\n", resposta); /*escreve no ficheiro de saida a resposta*/
    }
}

/** \brief realiza o modo da fase final
 *
 * \param fp_in FILE* ficheiro de entrada
 * \param fp_out FILE* ficheiro de saida
 * \return void
 *
 */
void modo2(FILE *fp_in, FILE *fp_out)
{
    lab_t maze = init_lab();
    int **tab = NULL;
    int tamanho = 0, resposta = 1, salas = 0, sala_final = 0, flag = 0;
    int *st = NULL, *wt = NULL;
    Graph *graph = NULL;

    while (fp_in != NULL)
    {
        if (fscanf(fp_in, "%d %d %d %d %d", &maze.linhas, &maze.colunas, &maze.solx, &maze.soly, &maze.blocos) != 5)
            break;

        /*se a coordenada estiver fora do tabuleiro*/
        if (check_if_outside(maze, maze.solx, maze.soly) == -2)
        {
            fill(maze, &tamanho, fp_in, fp_out, tab, 0);
            resposta = -1;
        }
        else
        {
            tab = init_tab(maze);
            fill(maze, &tamanho, fp_in, fp_out, tab, 1);

            /*se nao for uma celula branca*/
            if (A1(tab, maze.solx, maze.soly) != 0)
                resposta = -1;

            /*se forem ambas celulas brancas e pertencerem a mesma sala*/
            else if (A6(tab, maze, 1, 1, 1, &salas) == 1)
                resposta = 0;
        }
        /*se as coordenadas estiverem na mesma sala ou se a coordenada
        dada estiver fora do tabuleiro*/
        if (resposta == 0 || resposta == -1)
        {
            if (flag == 1)
                fprintf(fp_out, "\n\n");

            fprintf(fp_out, "%d\n", resposta);
            if (check_if_outside(maze, maze.solx, maze.soly) != -2)
                free_tab(tab, maze);
        }
        else
        {
            sala_final = -tab[maze.solx - 1][maze.soly - 1] - 3;

            graph = readGraph(salas, maze, tab);

            st = (int *)malloc(graph->vertex * sizeof(int));
            if (st == NULL)
                exit(1);

            wt = (int *)malloc(graph->vertex * sizeof(int));
            if (wt == NULL)
                exit(1);

            Dijkstras(graph, sala_final, st, wt);

            /*se o labirinto nao tiver solucao*/
            if (st[0] == -1)
            {
                if (flag == 1)
                    fprintf(fp_out, "\n\n");

                fprintf(fp_out, "%d\n", -1);
            }
            else
            {
                if (flag == 1)
                    fprintf(fp_out, "\n\n");

                fprintf(fp_out, "%d\n", wt[0]); /*custo do caminho*/

                print_file(graph, fp_out, st, 1); /*total de paredes partidas*/
                print_file(graph, fp_out, st, 0); /*quais paredes partidas*/
            }
            free(st);
            free(wt);
            freeGraph(graph);
        }
        salas = 0;
        tamanho = 0;
        resposta = 1;
        flag = 1;
    }
}