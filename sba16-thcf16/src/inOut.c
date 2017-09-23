
#include "matriz.h"
#include "inOut.h"

/**
 * @file inOut.h
 * @author Stephanie Briere Americo, Talita Halboth Cunha Fernandes
 * @date 23 Sep 2017
 * @brief Funções referentes à entrada 
 * e saída de arquivos
 *
 */

FILE *out;
//retorna o numero k de iterações
int trataArgumentos (int argc, char** argv,char** entrada, char** saida, int *N)
{
    *entrada = NULL;
    *saida = NULL; 
    *N = -1;
    int k = 0;
    for (int i = 0; i < argc; ++i)
    {
        if (argv[i][0]=='-')
        {
            if (argv[i][1]=='e')
            {
                *entrada = (char*)malloc(strlen(argv[2]) + 1);
                strcpy(*entrada, argv[i+1]);
            }
            else if (argv[i][1]=='o')
            {
                *saida =  (char*)malloc(strlen(argv[i+1]) + 1);
                strcpy(*saida, argv[i+1]);
            }
            else if (argv[i][1]=='r')
                *N = atoi (argv[i+1]);
            else if (argv[i][1]=='i')
                k = atoi (argv[i+1]);
        }
    }
    return k;
}

int entradaPorArquivo (char *entrada, MATRIZ *matriz)
{
#ifdef DEBUG
    printf("[ENTRADAPORARQUIVO] Iniciando leitura de arquivos.\n");
#endif
    FILE *in = NULL;
    if (entrada != NULL)
    {
        in = fopen(entrada, "r");
    }
    else
    {
        in = stdin;
    }
    if (!in)
    {
    #ifdef DEBUG
        printf("[ENTRADAPORARQUIVO] Falha ao abrir o arquivo de entrada.\n");
    #endif
        fprintf(stderr, " Falha ao abrir o arquivo de entrada.\n");
        return -1;
    }

    fscanf(in,"%d", &matriz->tam);
    if (!(matriz->dados = (double *)malloc(matriz->tam*matriz->tam*sizeof(double))))
    {
    #ifdef DEBUG
        printf("[ENTRADAPORARQUIVO] Falha ao alocar a matriz.\n");
    #endif
        fprintf(stderr, "Falha ao alocar a matriz.\n");
        return -1;
    }
    for (int i = 0; i < matriz->tam*matriz->tam; ++i)
    {
        fscanf(in,"%lf", &matriz->dados[i]);
    }
    fclose (in);
#ifdef DEBUG
    printf("[ENTRADAPORARQUIVO] Leitura de arquivos completa.\n");
#endif
    return 0;

}

int saidaPorArquivo(char *saida)
{
    if (saida == NULL)
    {
        out = stdout;
        return 0;
    }
    out = fopen(saida,"w");
    if (!out)
    {
    #ifdef DEBUG
        printf("[SAIDAPORARQUIVO] Falha ao abrir o arquivo de saida.\n");
    #endif
        fprintf(stderr, " Falha ao abrir o arquivo de saida.\n");
        return -1;
    }
    return 0;
}
