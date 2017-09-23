#ifndef __MATRIZ_H__
#define __MATRIZ_H__

/**
 * @file inOut.h
 * @author Stephanie Briere Americo, Talita Halboth Cunha Fernandes
 * @date 23 Sep 2017
 * @brief Header com funções e estruturas de dados
 * referentes à manipoulação de matrizes 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Estrutura de dados para representar uma matriz
 * 
 * 
 */
typedef struct MATRIZ {
    unsigned int tam; /**< Inteiro que representa o tamanho da matriz */
    double *dados; /**< Vetor de double par armazenar os dados da matriz */
} MATRIZ;


/**
 * @brief Função que faz a retrosubstituição de um sistema linear
 *
 * Esta funlção é implementada especificamente para resolver
 * sistemas lineares utilizando matrizes LU, através da resolução
 * de sistemas lineares do tipo LU*X=B, calculando o sistema com base
 * em cada coluna de X e B. 
 * O sistema linear foi dividido em L*Y=B e U*X=Y. substituicao_Lyb resolve
 * o sistema L*Y=B. 
 * @param L É uma matriz do tipo #MATRIZ, resultante da fatoração LU
 * da matriz original.
 * @param y É uma matriz do tipo #MATRIZ, que será usada para guardar
 * os elementos da solução do sistema.
 * @param b é um vetor auxiliar do tipo double.
 * @param itentity é uma flag que indica se a matriz B é a identidade.
 * 
 */
double *geraMatrizQuadradaRandomica(unsigned int n);

void imprimeMatriz (MATRIZ matriz);
void trocaLinhas (MATRIZ *matriz, unsigned int l1, unsigned int l2);
int pivotamentoParcial (MATRIZ *matriz, unsigned int col);
unsigned int pos(unsigned int lin, unsigned int col, unsigned int tam);
#endif