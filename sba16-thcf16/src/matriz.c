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

void imprimeMatriz (double *matriz, unsigned int tam) {
  printf("Matriz %ux%u\n", tam, tam);
  fprintf(stderr, "TROCAR LF POR G\n");
  for (int i = 0; i < tam; ++i) {
    for (int j = 0; j < tam; ++j) {
      if (matriz[pos(i, j, tam)] == 0) matriz[pos(i, j, tam)] = 0;
        if (matriz[pos(i, j, tam)] >= 0) printf(" ");
        // usar %.17g porque lf arredonda...
        printf("%.17lf  ", matriz[pos(i, j, tam)]);
    }
      printf("\n");
  }
}

unsigned int pos(unsigned int lin, unsigned int col, unsigned int tam) {
  return (lin*tam + col);
}