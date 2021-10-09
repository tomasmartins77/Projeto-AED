#include "Utility.h"
#include "Funcionalidades.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void modo1(char* filename, FILE* ficheiro);

int main(int argc, char *argv[])
{
    FILE *ficheiro;
    //ver nome ficheiro antes de o abrir
    if(check_filename(argv[2]) == 1)
    {
        if (argc != 3 || strcmp(argv[1], "-s") != 0)
        exit(1);

        ficheiro = fopen(argv[2], "r");
        if (ficheiro == NULL)
        {
            exit(EXIT_FAILURE);
        }

        modo1(argv[2], ficheiro);
    }
    return 0;
}

void modo1(char* filename, FILE* ficheiro)
{
    lab_t lab = init_maze();
    int aux_x = 0, aux_y = 0, aux_custo = 0, aux_tamanho = 0, resposta = 0;
    FILE* fp;
    int** tab = NULL;
    char* file_end = (char*)malloc(strlen(filename) * sizeof(char) + 2);
    if(file_end == NULL)
        exit(1);

    strcpy(file_end, change_ex(filename));

    free(file_end);

    fp = fopen("adsasdaddsa.sol1", "w");
    if(fp == NULL)
        exit(1);

    while(ficheiro != NULL)
    {
        if(fscanf(ficheiro,"%d %d %d %d %s %d", &lab.linhas, &lab.colunas, &lab.solx, &lab.soly, lab.pergunta, &lab.blocos) != 6)
            break;
        
        tab = init_tab(lab);

        while (aux_tamanho != lab.blocos)
        {
            if(fscanf(ficheiro, "%d %d %d", &aux_x, &aux_y, &aux_custo) != 3)
            {
                close_files(ficheiro, fp);
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
        fprintf(fp, "%d\n\n", resposta);
    }
    close_files(ficheiro, fp);   
}