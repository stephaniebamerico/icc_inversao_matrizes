#ifndef __MATRIZ_H__
#define __MATRIZ_H__

/**
 * @file matriz.h
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
 * @brief Função que gera uma matriz quadrada aleatória
 *
 * @param n é o tamanho da matriz a ser gerada
 * \return Retorna o ponteiro para uma matriz
 *
 */
double *geraMatrizQuadradaRandomica(unsigned int n);

/**
 * @brief Função que imprime os elementos de uma matriz
 *
 */
void imprimeMatriz (MATRIZ matriz);

/**
 * @brief Função que troca duas linhas de uma matriz
 * @param matriz é um ponteiro para a matriz a ser alterada
 * @param l1 é uma das linhas a ser trocada
 * @param l2 é uma das linhas a ser trocada
 *
 */
void trocaLinhas (MATRIZ *matriz, unsigned int l1, unsigned int l2);

/**
 * @brief Função que realiza pivotamento parcial em uma matriz para a fatoração LU
 * @param matriz é um ponteiro para a matriz a ser alterada
 * @param col é a coluna onde deve ser realizado o pivotamento
 * \return @c 0 se foi possível realizar o pivotamento
 * \return @c -1 se não foi possível realizar o pivotamento
 * 
 */
int pivotamentoParcial (MATRIZ *matriz, unsigned int col);

/**
 * @brief Função que calcula a posição @p lin x @p col da uma matriz de tamanho @p tam * @p tam, alocada em um vetor
 * @param lin é a linha da matriz
 * @param col é a coluna da matriz
 * @param tam é o tamanho da matriz
 * \return Retorna um inteiro que é a posição no vetor
 * 
 */
unsigned int pos(unsigned int lin, unsigned int col, unsigned int tam);
int alocaMatrizQuadrada(MATRIZ *matriz);
#endif