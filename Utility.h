#ifndef Utility
#define Utility

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modos.h"

/** \brief
 *
 */
int **init_tab(lab_t lab);

void shadow_fill(lab_t lab, int *aux_tamanho, FILE *fp_in, FILE *fp_out);

void fill(lab_t lab, int *aux_tamanho, FILE *fp_in, FILE *fp_out, int **tab);

/** \brief
 *
 */
lab_t init_maze();

/** \brief
 *
 */
void free_tab(int **tab, lab_t lab);

/** \brief
 *
 */
int check_if_outside(lab_t lab, int x, int y);

/** \brief
 *
 */
int check_filename(char *filename, int offset);

/** \brief
 *
 */
char *change_ex(char *filename);

/** \brief
 *
 */
void close_files(FILE *fp1, FILE *fp2);

/** \brief
 *
 */
int verifica_coord(lab_t lab, int custo);

void conn(int *tab_id, int *tab_size, int i, int j);

#endif
