#ifndef Utility
#define Utility

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modos.h"

/** \brief inicializa o tabuleiro
 *
 */
int **init_tab(lab_t lab);

/** \brief coloca os valores do ficheiro no labirinto ou passa as linhas do ficheiro
 *         a frente quando os valores das coordenadas estao fora do labirinto
 *
 */
void fill(lab_t lab, int *aux_tamanho, FILE *fp_in, FILE *fp_out, int **tab, int flag);

/** \brief inicializa todos os valores da struct
 *
 */
lab_t init_lab();

/** \brief liberta a memória alocada para todo o tabuleiro
 *
 */
void free_tab(int **tab, lab_t lab);

/** \brief verifica se a coordenada se encontra dentro do tabuleiro
 *
 */
int check_if_outside(lab_t lab, int x, int y);

/** \brief verifica se o ficheiro tem a extensao correta
 *
 */
int check_filename(char *filename, int offset);

/** \brief muda a extencao do ficheiro de saida para .sol1
 *
 */
char *change_ex(char *filename, int offset);

/** \brief funcao que fecha ambos os ficheiros
 *
 */
void close_files(FILE *fp1, FILE *fp2);

/** \brief verifica, de acordo com o algorimo A2-A4 lido do ficheiro de entrada a cor da celula
 *         de acordo com o custo de cada uma
 *
 */
int verifica_coord(lab_t lab, int custo);

/** \brief algoritmo de conectividade
 *
 */
void conn(int *tab_id, int *tab_size, int i, int j);

#endif
