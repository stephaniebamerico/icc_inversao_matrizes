#include "matriz.h"

void fatoracaoLU (MATRIZ *matriz);
void substituicao_Lyb (MATRIZ L, MATRIZ *y);
void troca (MATRIZ *matriz, unsigned int l1, unsigned int l2);
int pivotamentoParcial (MATRIZ *matriz, unsigned int col);

int main (int argc, char const *argv[]) {
    srand( 20172 );

    MATRIZ matriz;
    matriz.tam = 3; // 1 < tam < 32768

    if(! (matriz.dados = generateSquareRandomMatrix(matriz.tam)) ) {
        fprintf(stderr, "Erro ao alocar a matriz usando generateSquareRandomMatrix.\n");
        return 0;
    }

    imprimeMatriz(matriz);

    fatoracaoLU(&matriz);
    
    imprimeMatriz(matriz);

    MATRIZ x;

    substituicao_Lyb(matriz, &x);

    imprimeMatriz(x);

    return 0;
}

void fatoracaoLU (MATRIZ *matriz) {
    double m;
    for (int col = 0; col < matriz->tam-1; ++col) {
        pivotamentoParcial(matriz, col);            
            for (int lin = col+1; lin < matriz->tam; ++lin) {
                m = (matriz->dados[pos(lin, col, matriz->tam)]*1.0)/matriz->dados[pos(col, col, matriz->tam)];
                // U
                for (int j = col; j < matriz->tam; ++j)
                        matriz->dados[pos(lin, j, matriz->tam)] -= m*matriz->dados[pos(col, j, matriz->tam)];
                // L
                matriz->dados[pos(lin, col, matriz->tam)] = m;
            }
    }   
}

int pivotamentoParcial (MATRIZ *matriz, unsigned int col) {
    unsigned int max = col;
    for (unsigned int l_atual = col+1; l_atual < matriz->tam; ++l_atual)
        if (matriz->dados[pos(max, col, matriz->tam)] < matriz->dados[pos(l_atual, col, matriz->tam)])
            max = l_atual;

    if (matriz->dados[pos(max, col, matriz->tam)] == 0) {
        fprintf(stderr, "Matriz singular, impossivel fatorar.\n");
        return -1;
    }
    else if (max != col) troca (matriz, max, col);

    return 0;
}

void troca (MATRIZ *matriz, unsigned int l1, unsigned int l2) {
    double aux;
    for (int i = 0; i < matriz->tam; ++i) {
        aux = matriz->dados[pos(l1, i, matriz->tam)];
        matriz->dados[pos(l1, i, matriz->tam)] = matriz->dados[pos(l2, i, matriz->tam)];
        matriz->dados[pos(l2, i, matriz->tam)] = aux;
    }
}

void substituicao_Lyb (MATRIZ L, MATRIZ *y) {
	y->tam = L.tam;
	y->dados = (double *) calloc(y->tam, sizeof(double));

	for (int i = 0; i < y->tam; ++i) // inicia como uma matriz identidade
		y->dados[pos(i, i, y->tam)] = 1;

	for (int b = 0; b < y->tam-1; ++b) { // cada coluna da matriz é um vetor b para resolver o sistema
		for (int lin = 1; lin < y->tam; ++lin) { // da segunda linha até até a diagonal principal
			for (int col = b; col < lin; ++col) { // começa a partir da primeira valoração não nula (b)
				y->dados[pos(lin, b, y->tam)] -= L.dados[pos(lin, col, L.tam)]*y->dados[pos(col, b, y->tam)];
			}
		}
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