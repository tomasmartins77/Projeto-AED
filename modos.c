
#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"

/** \brief realiza o modo da fase intermedia
 *
 * \param fp_in FILE* ficheiro de entrada
 * \param fp_out FILE* ficheiro de saida
 * \return void
 *
 */
void modo1(FILE *fp_in, FILE *fp_out)
{
    lab_t lab = init_maze(); /*inicializa a struct que vai receber os valores dos ficheiros*/
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
        while (aux_tamanho != lab.blocos)
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
