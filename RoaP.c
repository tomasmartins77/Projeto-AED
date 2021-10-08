#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

typedef struct labirinto
{
    int linhas;
    int colunas;
    int solx;
    int soly;
    int blocos;
    char pergunta[3];
} lab_t;

char* change_ex(char* filename);

void inserir_dados(char *linha, int aux, lab_t *lab);

int check_if_outside(lab_t lab);

int A1(int** tab, lab_t lab);

int* A2(int** tab, lab_t lab);


int menu_perguntas(int** tab, lab_t lab)
{
    
    if(strcmp(lab.pergunta, "A1") == 0)
    {
        return A1(tab, lab);
    }/*
    if(strcmp(lab.pergunta, "A2"))
    {
        return A2(tab, lab);
    }
    if(strcmp(lab.pergunta, "A3"))
    {
        return A3(tab, lab);
    }
    if(strcmp(lab.pergunta, "A4"))
    {
        return A4(tab, lab);
    }
    if(strcmp(lab.pergunta, "A5"))
    {
        return A5(tab, lab);
    }
    if(strcmp(lab.pergunta, "A6"))
    {
        return A6(tab, lab);
    }*/
    exit(1);
}


void output_file(int resposta, char* filename, lab_t lab)
{
    FILE* ficheiro;

    char* file_end = (char*)malloc(strlen(filename) * sizeof(char) + 2);
    strcpy(change_ex(filename), file_end);

    ficheiro = fopen("adsasdaddsa.sol1", "w");
    if(ficheiro == NULL)
    {
        exit(1);
    }
       
    fprintf(ficheiro, "%d", resposta);

    fclose(ficheiro);
}

lab_t init_maze(){
    lab_t lab;
    lab.linhas = 0;
    lab.colunas = 0;
    lab.blocos = 0;
    lab.solx = 0;
    //lab.pergunta[3] = {'0', '0'};
    lab.soly = 0;
    return lab;
}

int** init_tab(lab_t lab)
{
    int **tab = (int **)calloc(lab.linhas, sizeof(int *));
        
        for (int i = 1; i <= lab.linhas; i++)
        {
            tab[i] = (int *)calloc(lab.colunas, sizeof(int));
        }
    return tab;
}

void modo1(char* filename, FILE* ficheiro)
{
    
    lab_t lab = init_maze();
    int aux_x = 0, aux_y = 0, aux_custo = 0, aux_tamanho = 0, resposta = 0;
    

    while(1)
    {
    if(fscanf(ficheiro,"%d %d %d %d %s %d", &lab.linhas, &lab.colunas, &lab.solx, &lab.soly, lab.pergunta, &lab.blocos) != 6)
    {
        fclose(ficheiro);
        exit(1);
    }

    if(check_if_outside(lab) == -2)
    {
        output_file(-2, filename, lab);
    }

    int** tab = init_tab(lab);

    while (fscanf(ficheiro, "%d %d %d", &aux_x, &aux_y, &aux_custo) != EOF)
    {
        if(aux_tamanho == lab.blocos)
        {
            aux_tamanho = 0;
            break;
        }

        tab[aux_x][aux_y] = aux_custo;

        aux_tamanho++;
    }
    
        resposta = menu_perguntas(tab, lab);
        output_file(resposta, filename, lab);

        if(feof(ficheiro) == 1)
        {
            fclose(ficheiro);
            break;
        }
    }
    
    fclose(ficheiro);   
}

int check_if_outside(lab_t lab)
{
    if(lab.solx > lab.linhas || lab.soly > lab.colunas || lab.solx < 1 || lab.soly < 1)
        return -2;
    return 0;
}

int A1(int** tab, lab_t lab)
{
    //ver se esta fora do maze
    int resultado = 0;
    return resultado = tab[lab.solx][lab.soly];
}
/*
int* A2(int** tab, lab_t lab)
{
    int i = 0, j = 0, a = 0, b = 0, offset_x = 0, offset_y = 0, z = 0;
    int vizinhos[9];

    for(a = 0; a < 3; a++)
    {
        for(b = 0; b < 3; b++)
        {
            for(i = -1; i < 2; i++)
            {
                for(j = -1; j < 2; j++, z++)
                {
                    offset_x = lab.solx + a + i;
                    offset_y = lab.soly + b + j;
                    if(offset_x >= 0 && offset_y >= 0 && offset_x < lab.linhas && offset_y < lab.colunas)
                    {
                        vizinhos[z] = tab[offset_x][offset_y];
                        
                    }
                }
            }
        }
    }
    return vizinhos;
}

int A3(int** tab, lab_t lab)
{
    
}

int A4(int** tab, lab_t lab)
{
    
}


int A5(int** tab, lab_t lab)
{
   
}

int A6(int** tab, lab_t lab)
{
    
}*/

int check_filename(char* filename)
{
    int i = 0, j = 0, t = 0;
    char ex[4];

    i = strlen(filename);
    t = i - 4;
    for(j = 0; t < i+1; j++, t++)
    {
        ex[j] = filename[t];
    }

    if(strcmp(ex, ".in1") == 0);
    return 1;
}

char* change_ex(char* filename)
{
    int i = 0, j = 0, t = 0;
    char ex[6] = ".sol1";

    i = strlen(filename);
    t = i - 5;
    for(j = 0; t < i+1; j++, t++)
    {
        filename[t+1] = ex[j];
    }
    return filename;

}

int main(int argc, char *argv[])
{
    FILE *ficheiro;
    //ver nome ficheiro antes de o abrir
    if(check_filename(argv[2]) == 0)
    {
        exit(1);
    }
    
    
    ficheiro = fopen(argv[2], "r");
    if (ficheiro == NULL)
    {
        exit(EXIT_FAILURE);
    }

    modo1(argv[2], ficheiro);


// ficheiros podem ter .in1 no meio do nome
    if (argc != 3 || strcmp(argv[1], "-s") != 0)
        exit(0);

    if (strstr(argv[2], ".in1") != 0)
    {
        modo1(argv[2], ficheiro);
    }
    else
        exit(0);

    return 0;
}