#include "matriz.h"

void fatoracaoLU (MATRIZ *matriz);
void substituicao_Lyb (MATRIZ L, MATRIZ *y);
void troca (MATRIZ *matriz, unsigned int l1, unsigned int l2);
int pivotamentoParcial (MATRIZ *matriz, unsigned int col);
void retrosubstituicao (MATRIZ U, MATRIZ *Y);
void retrosubstituicaoUxy (MATRIZ U, MATRIZ *y);

int main (int argc, char const *argv[]) {
    srand( 20172 );

    MATRIZ matriz;
    matriz.tam = 2; // 1 < tam < 32768

    if(! (matriz.dados = generateSquareRandomMatrix(matriz.tam)) ) {
        fprintf(stderr, "Erro ao alocar a matriz usando generateSquareRandomMatrix.\n");
        return 0;
    }

    matriz.dados[pos(0, 0, matriz.tam)]=2;
    matriz.dados[pos(0, 1, matriz.tam)]=1;
    matriz.dados[pos(1, 0, matriz.tam)]=5;
    matriz.dados[pos(1, 1, matriz.tam)]=3;

    imprimeMatriz(matriz);
    
    fatoracaoLU(&matriz);
    printf("matriz depois de LU:\n");
    imprimeMatriz(matriz);

    MATRIZ x;   
    substituicao_Lyb(matriz, &x);
    printf("x depois de Ly=b:\n");
    imprimeMatriz(x);
    retrosubstituicaoUxy(matriz,&x);
    printf("inv:\n");
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

void retrosubstituicaoUxy (MATRIZ U, MATRIZ *y) {
	double *b = NULL;
	if(! (b = (double *) malloc(U.tam*sizeof(double))) ){
		fprintf(stderr, "[retrosubstituicaoUxy]: impossível alocar b.\n");
		return;
	}

	for (int sl = 0; sl < U.tam; ++sl) {
		for (int i = 0; i < y->tam; ++i) {
			b[i] = y->dados[pos(i, sl, y->tam)];
		}
		for (int lin = U.tam-1; lin >= 0; --lin) {
			y->dados[pos(lin, sl, y->tam)] = b[lin];

			for (int col = lin+1; col < U.tam; ++col) {
				y->dados[pos(lin, sl, y->tam)] = U.dados[pos(lin, col, U.tam)]*y->dados[pos(col, sl, y->tam)];
			}

			y->dados[pos(lin, sl, y->tam)] /= U.dados[pos(lin, lin, U.tam)];
		}
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

double *residuo (MATRIZ A, MATRIZ inv_A) {
	double *r = NULL;
	if ( ! (r = (double *) malloc(A.tam*sizeof(double))) )
    	return NULL;
    // r = A * inv_A
    for(int lin=0; lin < A.tam; lin++) 
        for(col=0; col < A.tam; col++){ 
        	somaprod=0;
        	for(i=0; i < A.tam; i++)
          		somaprod += A[pos(lin, i, A->tam)]*inv_A[A[pos(i, col, A->tam)]]; 
        	r[pos(lin, col, A->tam)]=somaprod; 
		}

    return r;
}