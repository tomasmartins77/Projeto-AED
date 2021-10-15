
#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"

/** \brief
 *
 * \param fp_in FILE*
 * \param fp_out FILE*
 * \return void
 *
 */
void modo1(FILE *fp_in, FILE *fp_out)
{
    lab_t lab = init_maze();
    int aux_tamanho = 0, resposta = 0, sec_cordx = 0, sec_cordy = 0;
    int **tab = NULL;

    while (fp_in != NULL)
    {
        if (fscanf(fp_in, "%d %d %d %d %s", &lab.linhas, &lab.colunas, &lab.solx, &lab.soly, lab.pergunta) != 5)
            break;

        if (lab.pergunta[1] == '6')
        {
            if (fscanf(fp_in, "%d %d %d", &sec_cordx, &sec_cordy, &lab.blocos) != 3)
                break;

            if (check_if_outside(lab, lab.solx, lab.soly) == -2 || check_if_outside(lab, sec_cordx, sec_cordy) == -2)
                shadow_fill(lab, &aux_tamanho, fp_in, fp_out);

            else
                tab = init_tab(lab);
        }
        else
        {
            if (fscanf(fp_in, "%d", &lab.blocos) != 1)
                break;

            if (check_if_outside(lab, lab.solx, lab.soly) == -2)
                shadow_fill(lab, &aux_tamanho, fp_in, fp_out);

            else
                tab = init_tab(lab);
        }

        while (aux_tamanho != lab.blocos)
        {
            tab = fill(lab, &aux_tamanho, fp_in, fp_out, tab);
        }

        if (check_if_outside(lab, lab.solx, lab.soly) == -2 || (lab.pergunta[1] == '6' && check_if_outside(lab, sec_cordx, sec_cordy) == -2))
            resposta = -2;
        else
        {
            resposta = menu_perguntas(tab, lab, sec_cordx, sec_cordy);
            free_tab(tab, lab);
        }

        aux_tamanho = 0;
        fprintf(fp_out, "%d\n\n", resposta);
    }
    close_files(fp_in, fp_out);
}
