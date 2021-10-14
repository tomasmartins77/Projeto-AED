#ifndef modos
#define modos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct labirinto
{
    int linhas;
    int colunas;
    int solx;
    int soly;
    int blocos;
    char pergunta[3];
} lab_t;

/** \brief
 *
 */
void modo1(FILE *fp_in, FILE *fp_out);

#endif
