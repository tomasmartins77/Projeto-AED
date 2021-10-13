#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"

void modo1(FILE *fp_in, FILE *fp_out)
{
    lab_t lab = init_maze();
    int aux_x = 0, aux_y = 0, aux_custo = 0, aux_tamanho = 0, resposta = 0;
    int** tab = NULL;
    int sec_cordx = 0, sec_cordy = 0;

    while(fp_in != NULL)
    {
        if(fscanf(fp_in,"%d %d %d %d %s %d", &lab.linhas, &lab.colunas, &lab.solx, &lab.soly, lab.pergunta, &lab.blocos) != 6)
        {
            if(fscanf(fp_in,"%d %d %d %d %s %d %d %d", &lab.linhas, &lab.colunas, &lab.solx, &lab.soly, lab.pergunta, &sec_cordx, &sec_cordy, &lab.blocos) != 8)
                break;
        }
//sizeable03 501 linhas
        if(check_if_outside(lab, lab.solx, lab.soly) == -2)
        {
            while (aux_tamanho != lab.blocos)
            {
                if(fscanf(fp_in, "%d %d %d", &aux_x, &aux_y, &aux_custo) != 3)
                {
                    close_files(fp_in, fp_out);
                    return;
                }
                aux_tamanho++;
            }
        }
        else
            tab = init_tab(lab);
            
        while (aux_tamanho != lab.blocos)
        {
            if(fscanf(fp_in, "%d %d %d", &aux_x, &aux_y, &aux_custo) != 3)
            {
                close_files(fp_in, fp_out);
                free_tab(tab, lab);
                return;
            }
            if(check_if_outside(lab, lab.solx, lab.soly) != -2)
            {
                tab[aux_x-1][aux_y-1] = aux_custo;
                aux_tamanho++;
            }
        }
        if(check_if_outside(lab, lab.solx, lab.soly) == -2)
            resposta = -2;
        else{
            resposta = menu_perguntas(tab, lab, sec_cordx, sec_cordy);
            free_tab(tab, lab);
        }
        aux_tamanho = 0;
        fprintf(fp_out, "%d\n\n", resposta);
    }
    close_files(fp_in, fp_out);   
}