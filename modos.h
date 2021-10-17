#ifndef modos
#define modos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct labirinto
{
    int linhas;  /*linhas do labirinto*/
    int colunas; /*colunas do labirinto*/
    int solx;    /*coordenada a ser verificada*/
    int soly;
    int blocos;       /*numero de celulas nao brancas*/
    char pergunta[3]; /*A1-A6*/
} lab_t;

/** \brief realiza o modo da fase intermedias
 *
 */
void modo1(FILE *fp_in, FILE *fp_out);

#endif
