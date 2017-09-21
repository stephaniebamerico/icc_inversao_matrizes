#ifndef __MATRIZ_H__
#define __MATRIZ_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MATRIZ {
    unsigned int tam; 
    double *dados;
} MATRIZ;

double *geraMatrizQuadradaRandomica(unsigned int n);
void imprimeMatriz (MATRIZ matriz);
void trocaLinhas (MATRIZ *matriz, unsigned int l1, unsigned int l2);
int pivotamentoParcial (MATRIZ *matriz, unsigned int col);
unsigned int pos(unsigned int lin, unsigned int col, unsigned int tam);
#endif