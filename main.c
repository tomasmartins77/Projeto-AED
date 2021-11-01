#include "modos.h"
#include "Utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp_in;
    FILE *fp_out;

    char *file_end = (char *)malloc(strlen(argv[2]) * sizeof(char) + 2);
    if (file_end == NULL)
        exit(1);

    /*se o formato de invocacao do programa for correto e o ficheiro tiver a extensao correta*/
    if (argc == 3 && check_filename(argv[2], 4) == 1 && strcmp(argv[1], "-s") == 0)
    {
        /*muda a extensao do file_end*/
        strcpy(file_end, change_ex(argv[2], 4));
        /*abre o ficheiro para leitura*/
        fp_in = fopen(argv[2], "r");
        if (fp_in == NULL)
        {
            free(file_end);
            exit(1);
        }

        fp_out = fopen(file_end, "w");
        if (fp_out == NULL)
        {
            fclose(fp_in);
            free(file_end);
            exit(1);
        }
        free(file_end);
        /*abre o ficheiro para escrita*/
        modo1(fp_in, fp_out);
    }
    else if (argc == 2 && check_filename(argv[1], 3) == 1)
    {
        /*muda a extensao do file_end*/
        strcpy(file_end, change_ex(argv[1], 3));
        /*abre o ficheiro para leitura*/
        fp_in = fopen(argv[1], "r");
        if (fp_in == NULL)
        {
            free(file_end);
            exit(1);
        }

        fp_out = fopen(file_end, "w");
        if (fp_out == NULL)
        {
            fclose(fp_in);
            free(file_end);
            exit(1);
        }
        free(file_end);
    }

    close_files(fp_in, fp_out);
    return 0;
}