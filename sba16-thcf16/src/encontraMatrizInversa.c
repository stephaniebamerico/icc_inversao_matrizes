#include "matriz.h"

void troca (double **matriz, unsigned int tam, unsigned int l1, unsigned int l2);
int pivotamentoParcial (double **matriz, unsigned int tam, unsigned int col);
void fatoracaoLU (double **matriz, unsigned int tam);

int main (int argc, char const *argv[]) {
    srand( 20172 );

    unsigned int tam = 5; // 1 < tam < 32768

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

void troca (double **matriz, unsigned int tam, unsigned int l1, unsigned int l2) {
    double aux;
    for (int i = 0; i < tam; ++i) {
        aux = (*matriz)[pos(l1, i, tam)];
        (*matriz)[pos(l1, i, tam)] = (*matriz)[pos(l2, i, tam)];
        (*matriz)[pos(l2, i, tam)] = aux;
    }
}

/*int retrosubstituicao (double **A, unsigned int tam, double *x, unsigned int b) {
    double soma = 0;
    x[tam-1] = (b == tam-1 ? 1 : 0); // b é a coluna da matriz identidade
    x[tam-1] /= A[pos(tam, tam-1, tam-1)];
    for (int lin = tam-2; lin >= 0; --lin) {
        soma = (b == lin ? 1 : 0);

        for (int col = lin; col < tam; ++col)
            soma-= A[lin][col]*(x[col]);
        
        x[lin]=(soma*1.0)/A[lin][lin];
    }

    for (int i = 0; i < N; ++i) {
        if (x[i] == 0) x[i] = 0;
        if (x[i] >= 0) printf(" ");
        printf("%.17lf \n", x[i]);
    }
    
    return 0;
}*/