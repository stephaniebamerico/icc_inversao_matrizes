#include "matriz.h"

void troca (double **matriz, unsigned int tam, unsigned int l1, unsigned int l2) {
    double aux;
    for (int i = 0; i < tam; ++i) {
        aux = (*matriz)[pos(l1, i, tam)];
        (*matriz)[pos(l1, i, tam)] = (*matriz)[pos(l2, i, tam)];
        (*matriz)[pos(l2, i, tam)] = aux;
    }
}

int pivotamentoParcial (double **matriz, unsigned int tam, unsigned int col) {
    unsigned int max = col;
    for (unsigned int l_atual = col+1; l_atual < tam; ++l_atual)
        if ((*matriz)[pos(max, col, tam)] < (*matriz)[pos(l_atual, col, tam)])
            max = l_atual;

    if ((*matriz)[pos(max, col, tam)] == 0) {
        fprintf(stderr, "Matriz singular, impossivel fatorar.\n");
        return -1;
    }
    else if (max != col) troca (matriz, tam, max, col);

    return 0;
}

void fatoracaoLU (double **matriz, unsigned int tam) {
    double m;
    for (int col = 0; col < tam-1; ++col) {
        pivotamentoParcial(matriz, tam, col);            
            for (int lin = col+1; lin < tam; ++lin) {
                m = ((*matriz)[pos(lin, col, tam)]*1.0)/(*matriz)[pos(col, col, tam)];
                // U
                for (int j = col; j < tam; ++j)
                        (*matriz)[pos(lin, j, tam)] -= m*(*matriz)[pos(col, j, tam)];
                // L
                (*matriz)[pos(lin, col, tam)] = m;
            }
    }   
}

/*int resolve (double a[N][N], double x[N], double b[N]) {
    double soma = 0;
    x[N-1] = b[N-1]/a[N-1][N-1];
    for (int k = N-2; k >= 0; --k) {
        soma = b[k];

        for (int j = k; j < N; ++j)
            soma-= a[k][j]*(x[j]);
        
        x[k]=(soma*1.0)/a[k][k];
    }

    for (int i = 0; i < N; ++i) {
        if (x[i] == 0) x[i] = 0;
        if (x[i] >= 0) printf(" ");
        printf("%.20lf \n", x[i]);
    }
    
    return 0;
}*/

int main (int argc, char const *argv[]) {
    srand( 20172 );

    unsigned int tam = 3;

    double *matriz = NULL;

    if(! (matriz = generateSquareRandomMatrix(tam)) ) {
        fprintf(stderr, "Erro ao alocar a matriz usando generateSquareRandomMatrix.\n");
        return 0;
    }

    imprimeMatriz(matriz, tam);

    fatoracaoLU(&matriz, tam);
    
    imprimeMatriz(matriz, tam);

    return 0;
}