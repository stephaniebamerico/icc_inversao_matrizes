#include "matriz.h"
#include <math.h>

int fatoracaoLU (MATRIZ *matriz);
int substituicao_Lyb (MATRIZ L, MATRIZ *y);
int substituicao_Uxy (MATRIZ U, MATRIZ *y, double *b);
double refinamento(MATRIZ A, MATRIZ inv_A);

int main (int argc, char const *argv[]) {
	srand( 20172 );

	MATRIZ original, originalLU, inversa;
	original.tam = 100; // 1 < tam < 32768
	originalLU.tam = original.tam;    
	double *aux = NULL;

	// lê a matriz original... (alterar)
	if(! (original.dados = geraMatrizQuadradaRandomica(original.tam)) ) {
#ifdef DEBUG
	printf("[MAIN] Falha ao alocar a matriz original.\n");
#endif
	fprintf(stderr, "Erro ao alocar a matriz original.\n");
		return 0;
	}

	// alocando a matriz que guardará a fatoração LU
	if (! (originalLU.dados = (double*)malloc (originalLU.tam*originalLU.tam*sizeof(double)))) {
#ifdef DEBUG
	printf("[MAIN] Falha ao alocar a matriz originalLU.\n");
#endif
		fprintf(stderr, "Erro ao alocar a matriz originalLU\n");
		return 0;
	}

	// copia matriz original para a matriz que sofrerá a fatoração LU
	for (int i = 0; i < original.tam*original.tam; ++i)
		originalLU.dados[i] = original.dados[i];
	
	fatoracaoLU(&originalLU); // fatora a matriz original em uma LU

	// funções retornam -1 se ocorrer algum problema   
	if (substituicao_Lyb(originalLU, &inversa) == -1) { // resolve o sistema L*y=b (o resultado é armazenado na inversa)
		fprintf(stderr, "Erro em substituicao_Lyb.\n");
		return 0;
	}
	if (substituicao_Uxy(originalLU, &inversa, aux) == -1) { // resolve o sistema U*x=y (o resultado é armazenado na inversa)
		return 0;
		fprintf(stderr, "Erro em substituicao_Uxy.\n");
	}

	//imprimeMatriz(inversa);
	 
	// neste ponto, a inversa deveria estar correta... partimos para o refinamento
	double r = refinamento(original, inversa);
	printf("r = %.17lf\n", r);
	free(original.dados);
	free(originalLU.dados);
	free(inversa.dados);
	//free(aux);
	 
	return 0;
}

int fatoracaoLU (MATRIZ *matriz) {
#ifdef DEBUG
	printf("[FATORACAOLU] Iniciando a fatoracao LU.\n");
#endif
	double m;
	for (int col = 0; col < matriz->tam-1; ++col) { // zerando colunas
		if(pivotamentoParcial(matriz, col) == -1) { // se o pivotamento falha, a matriz é inválida
			fprintf(stderr, "[fatoracaoLU] Matriz singular, impossivel fatorar.\n");
			return -1;
		}
		for (int lin = col+1; lin < matriz->tam; ++lin) { // calcula o modificador m para cada linha
			m = (matriz->dados[pos(lin, col, matriz->tam)]*1.0)/matriz->dados[pos(col, col, matriz->tam)];
			// U
			for (int j = col; j < matriz->tam; ++j) // percorrendo linha para aplicar m
				matriz->dados[pos(lin, j, matriz->tam)] -= m*matriz->dados[pos(col, j, matriz->tam)];
			// L
			matriz->dados[pos(lin, col, matriz->tam)] = m; // armazena o modificador m onde seria 0
		}
	} 
#ifdef DEBUG
	printf("[FATORACAOLU] Fatoracao LU completa.\n");
#endif 
	return 0;
}

int substituicao_Lyb (MATRIZ L, MATRIZ *y) {
#ifdef DEBUG
	printf("[SUBSTITUICAO_LYB] Iniciando a resolucao do sistema Ly=b.\n");
#endif
	// variavel auxiliar pro tamanho das matrizes
	unsigned int tam = L.tam;
	y->tam = tam;
	if (!(y->dados = (double *) calloc(tam*tam, sizeof(double)))) {
		fprintf(stderr,"[substituicao_Lyb] Erro ao alocar a matriz y.\n");
		return 0;
	}

	for (int i = 0; i < tam; ++i) // y inicia como uma matriz identidade
		y->dados[pos(i, i, tam)] = 1;

	for (int b = 0; b < tam-1; ++b) { // cada coluna da matriz é um vetor b (A*x=b) para resolver o sistema
		for (int lin = 1; lin < tam; ++lin) { // da segunda linha em diante (a primeira sofre alteração)
			for (int col = b; col < lin; ++col) { // começa a partir da primeira valoração não nula (b)
				y->dados[pos(lin, b, tam)] -= L.dados[pos(lin, col, tam)]*y->dados[pos(col, b, tam)];
			}
		}
	}
#ifdef DEBUG
	 printf("[SUBSTITUICAO_LYB] Resolucao do sistema Ly=b completa.\n");
#endif 
	return 0;
}

int substituicao_Uxy (MATRIZ U, MATRIZ *y, double *b) {
#ifdef DEBUG
	printf("[SUBSTITUICAO_UXY] Iniciando a resolucao do sistema Ux=y.\n");
#endif
	// variavel auxiliar pro tamanho das matrizes
	unsigned int tam = U.tam;
	// vetor auxiliar (b de A*x=b), pois utilizaremos a matriz y para armazenar a matriz resultante
	//double *b ;
	// aloca memória para o vetor b
	if (!(b = (double*)(calloc (tam, sizeof(double))))) {
		fprintf(stderr,"[substituicao_Uxy] Erro ao alocar vetor auxiliar b.\n");
		return -1;
	}
	// i é a coluna da matriz na qual estamos realizando a substituição (cada coluna é o vetor b de um sistema linear A*x=b)
	for (int i = 0; i < tam; ++i) {
		// y será alterado para armazenar a matriz resultante (funcionando como x em Ax = b)
		// a coluna i de y é copiada para o vetor b
		for (int k = 0; k < tam; ++k)
			b[k] = y->dados[pos(k,i,tam)];
		// faz a retrosubstituição 
		y->dados[pos(tam-1,i,tam)] = (b[tam-1]*1.0)/U.dados[pos(tam-1, tam-1, tam)];
		for (int k = tam-1; k >= 0; --k) {
			y->dados[pos(k,i,tam)] = b[k];
			for (int j = tam-1; j > k; --j)
				y->dados[pos(k,i,tam)] -= U.dados[pos(k,j,tam)]*y->dados[pos(j,i,tam)];
			y->dados[pos(k,i,tam)]=(y->dados[pos(k,i,tam)]*1.0)/U.dados[pos(k,k,tam)];
		}        
	}
#ifdef DEBUG
	printf("[SUBSTITUICAO_UXY] Resolucao do sistema Ux=y completa.\n");
#endif 
	free(b);
	return 0;
}

double refinamento(MATRIZ A, MATRIZ inv_A) {
#ifdef DEBUG
	printf("[MULTIPLICAMATRIZES] Iniciando multiplicacao de matrizes %ux%u.\n", A.tam, A.tam);
#endif
	unsigned int tam = A.tam;
	double C = 0, r = 0;
	for (int lin = 0; lin < tam; lin++) {
		for (int col = 0; col < tam; col++) {
			C = 0;
			for (int k = 0; k < tam; k++)
				C += A.dados[pos(lin,k,tam)]*inv_A.dados[pos(k,col,tam)];
			C = (lin == col ? 1 - C : C); // R = I - A*inv_A 
			C *= C;
			r += (lin == col ? 1 - C : C); // ||r|| = sum(R[i,j]^2)
		}
	}
	r = sqrt(r); // ||r|| = sqrt(sum(R[i,j]^2))

	return r;
}