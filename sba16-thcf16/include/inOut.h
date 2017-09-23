#ifndef __INOUT_H__
#define __INOUT_H__

/**
 * @file inOut.h
 * @author Stephanie Briere Americo, Talita Halboth Cunha Fernandes
 * @date 23 Sep 2017
 * @brief Header com funções referentes à entrada 
 * e saída de arquivos
 *
 */

extern FILE *out;
int trataArgumentos (int argc, char** argv,char** entrada, char** saida, int *N);
int entradaPorArquivo (char *entrada, MATRIZ *matriz);
int saidaPorArquivo (char *saida);

#endif