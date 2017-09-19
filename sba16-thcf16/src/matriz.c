#include "matriz.h"

double *generateSquareRandomMatrix( unsigned int n ) {
  double *mat = NULL;

  /* return NULL if memory allocation fails */
  if ( ! (mat = (double *) malloc(n*n*sizeof(double))) )
    return (NULL);

  /* generate a randomly initialized matrix in row-major order */
  double *ptr = mat;
  double *end = mat + n*n;

  double invRandMax = 1.0/(double)RAND_MAX;

  while( ptr != end ) {
    *ptr++ = (double)rand() * invRandMax;
  }

  return (mat);
}

void imprimeMatriz (MATRIZ matriz) {
  printf("Matriz %ux%u\n", matriz.tam, matriz.tam);
  fprintf(stderr, "TROCAR LF POR G\n");
  for (int i = 0; i < matriz.tam; ++i) {
    for (int j = 0; j < matriz.tam; ++j) {
      if (matriz.dados[pos(i, j, matriz.tam)] == 0) matriz.dados[pos(i, j, matriz.tam)] = 0;
        if (matriz.dados[pos(i, j, matriz.tam)] >= 0) printf(" ");
        // usar %.17g porque lf arredonda...
        printf("%.17lf  ", matriz.dados[pos(i, j, matriz.tam)]);
    }
      printf("\n");
  }
}

unsigned int pos(unsigned int lin, unsigned int col, unsigned int tam) {
  return (lin*tam + col);
}