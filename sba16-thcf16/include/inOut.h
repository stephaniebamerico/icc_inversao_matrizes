#ifndef __INOUT_H__
#define __INOUT_H__

extern FILE *out;
int trataArgumentos (int argc, char** argv,char** entrada, char** saida, int *N);
int entradaPorArquivo (char *entrada, MATRIZ *matriz);
int saidaPorArquivo (char *saida);

#endif