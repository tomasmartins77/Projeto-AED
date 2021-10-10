#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"

void modo1(FILE *fp_in, FILE *fp_out)
{
    lab_t lab = init_maze();
    int aux_x = 0, aux_y = 0, aux_custo = 0, aux_tamanho = 0, resposta = 0;
    int** tab = NULL;
    

    while(fp_in != NULL)
    {
        if(fscanf(fp_in,"%d %d %d %d %s %d", &lab.linhas, &lab.colunas, &lab.solx, &lab.soly, lab.pergunta, &lab.blocos) != 6)
            break;
        
        tab = init_tab(lab);

        while (aux_tamanho != lab.blocos)
        {
            if(fscanf(fp_in, "%d %d %d", &aux_x, &aux_y, &aux_custo) != 3)
            {
                close_files(fp_in, fp_out);
                exit(1);
            }
            aux_x--;
            aux_y--;
            tab[aux_x][aux_y] = aux_custo;
            aux_tamanho++;
        }
        if(check_if_outside(lab) == -2)
        {
            resposta = -2;
        }else{
            resposta = menu_perguntas(tab, lab);
        }
        free_tab(tab, lab);
        aux_tamanho = 0;
        fprintf(fp_out, "%d\n\n", resposta);
    }
    close_files(fp_in, fp_out);   
}