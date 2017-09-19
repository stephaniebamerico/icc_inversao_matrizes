#ifndef __MATRIZ_H__
#define __MATRIZ_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct MATRIZ {
    unsigned int tam; 
    double *dados;
} MATRIZ;

double *generateSquareRandomMatrix(unsigned int n);
void imprimeMatriz (MATRIZ matriz);
unsigned int pos(unsigned int lin, unsigned int col, unsigned int tam);

#endif