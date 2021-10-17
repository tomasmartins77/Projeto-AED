#ifndef Funcionalidades
#define Funcionalidades

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modos.h"

/** \brief executa os algoritmos A1-A6 consoante o que foi lido no ficheiro de entrada
 *
 */
int menu_perguntas(int **tab, lab_t lab, int A6_x, int A6_y);

/** \brief retorna o valor de uma certa coordenada
 *
 */
int A1(int **tab, int x, int y);

/** \brief verifica quais os vizinhos de uma certa coordenada
 *
 */
int A234(int **tab, lab_t lab, int x, int y);

/** \brief verifica se a celula e cinzenta e quebravel
 *
 */
int A5(int **tab, lab_t lab);

/** \brief verifica se 2 celulas se encontram na mesma sala
 *
 */
int A6(int **tab, lab_t lab, int A6_x, int A6_y);

#endif
