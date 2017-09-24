/*! \mainpage notitle
 *
 * \authors Stephanie Briere Americo @b GRR29165313
 * \authors Talita Halboth Cunha Fernandes @b GRR29165399
 * @date 23 Sep 2017
 * \section intro_sec Introdução
 *
 * O objetivo deste trabalho é 
 * implementar um programa computacional que, 
 * dada uma matriz quadrada A de dimensão n, 
 * encontre a matriz inversa de A (inv(A)), tal que A * inv(A) 
 * = I, onde I é a matriz identidade.
 * Para tal, o programa utiliza o Método da Eliminação de Gauss com Pivotamento Parcial, Fatoração LU e Refinamento.
 *
 * \subsection install_sec Compilação
 * Há uma makefile no projeto que compila o código, gerando o executável @c invmat
 *
 * \subsection run_sec Rodando o programa
 * @verbatim invmat [-e arquivo_entrada] [-o arquivo_saida] [-r N] -i k@endverbatim
 *
 *<ul>
 *	<li> @c -e @c arquivo_entrada: parâmetro opcional no qual @c arquivo_entrada é o caminho completo para o arquivo contendo a matriz a ser invertida. Em caso de ausência do parâmetro, a entrada será lida de @c stdin.
 *	<li>@c -o @c arquivo_saida: parâmetro opcional no qual @c arquivo_saida é o caminho completo para o arquivo que vai conter a matriz inversa. Em caso de ausência do parâmetro, a saída será impressa em @c stdout.
 *	<li>@c -r @c N: parâmetro opcional no qual @c N é a dimensão da matriz de entrada a ser gerada aleatoriamente
 *	<li>@c -i @c k: Número de iterações de refinamento a serem executadas (>0)
 *
 *
 */


/**
 * @file encontraMatrizInversa.c
 * @author Stephanie Briere Americo GRR29165313
 * @author Talita Halboth Cunha Fernandes GRR29165399
 * @date 23 Sep 2017
 * @brief Código que realiza a inversão de matrizes através da fatoração LU, resolução de sistemas lineares e refinamento
 *
 */

#include "matriz.h"
#include "inOut.h"
#include <math.h>
#include <time.h>
#include <sys/time.h>

/**
 * @brief Função que faz a fatoração LU de uma matriz quadrada.
 *
 * Esta função recebe apenas um parâmetro, @p matriz do tipo #MATRIZ.
 * @param matriz é a matriz a ser fatorada.
 * \return @c 0 se a fatoração não deu erro
 * \return @c -1 se houve erro na fatoração
 *
 */
int fatoracaoLU (MATRIZ *matriz);

/**
 * @brief Função que faz a retrosubstituição de um sistema linear
 *
 * Esta funlção é implementada especificamente para resolver
 * sistemas lineares utilizando matrizes LU, através da resolução
 * de sistemas lineares do tipo LU*X=B, calculando o sistema com base
 * em cada coluna de X e B. 
 * O sistema linear foi dividido em L*Y=B e U*X=Y. substituicao_Lyb resolve
 * o sistema L*Y=B. 
 * @param L É uma matriz do tipo #MATRIZ, resultante da fatoração LU
 * da matriz original.
 * @param y É uma matriz do tipo #MATRIZ, que será usada para guardar
 * os elementos da solução do sistema.
 * @param b é um vetor auxiliar do tipo double.
 * @param itentity é uma flag que indica se a matriz B é a identidade.
 * \return @c 0 se a fatoração não deu erro
 * \return @c -1 se houve erro na fatoração
 */
int substituicao_Lyb (MATRIZ L, MATRIZ *y, double *b, int identity) ;

/**
 * @brief Função que faz a substituição avançada de um sistema linear
 *
 * Esta funlção é implementada especificamente para resolver
 * sistemas lineares utilizando matrizes LU, através da resolução
 * de sistemas lineares do tipo LU*X=B, calculando o sistema com base
 * em cada coluna de X e B. 
 * O sistema linear foi dividido em L*Y=B e U*X=Y. substituicao_Uxy resolve
 * o sistema L*Y=B. 
 * @param U É uma matriz do tipo #MATRIZ, resultante da fatoração LU
 * da matriz original.
 * @param y É uma matriz do tipo #MATRIZ, que será usada para guardar
 * os elementos da solução do sistema.
 * @param b é um vetor auxiliar do tipo double.
 * \return @c 0 se a fatoração não deu erro
 * \return @c -1 se houve erro na fatoração
 * 
 */
int substituicao_Uxy (MATRIZ U, MATRIZ *y, double *b);

/**
 * @brief Função que faz a substituição avançada de um sistema linear
 * Faz o refinamento.
 * \return @c 0 se a fatoração não deu erro
 * \return @c -1 se houve erro na fatoração
 * 
 */
int refinamento(MATRIZ A, MATRIZ *inv_A, MATRIZ LU, double *aux, int iter);
void calculaResiduo(MATRIZ A, MATRIZ inv_A, MATRIZ *R);

double timestamp (void);

/**
 * @brief Função para calcular o reíduo.
 * 
 */
void residuo(MATRIZ LU, MATRIZ B, MATRIZ *R);


int main (int argc, char** argv) {

	srand( 20172 );
	int n, iteracoes; // tam da matriz e iteracoes do refinamento
	char *arqEntrada , *arqSaida;
	MATRIZ original, originalLU, inversa; // matrizes utilizadas
	double *aux = NULL;
	double tempo;
	out = stdout;

	trataArgumentos(argc, argv, &arqEntrada, &arqSaida, &n, &iteracoes);	   
	if (arqSaida != NULL) 
		saidaPorArquivo(arqSaida);
	
	//leitura dos dados da matriz
	if (n == -1) {
		if (entradaPorArquivo(arqEntrada,&original) == -1)
			return 0;
		n = original.tam; // usaremos n como tam da matriz
	}
	else { //caso não se defina nenhum arquivo de entrada e nem o tamanho da matriz, cria uma matriz aleatoria
		original.tam = n;
		if(! (original.dados = geraMatrizQuadradaRandomica(n)) ) {
			fprintf(stderr, "Erro ao alocar a matriz original.\n");
			return 0;
		}
	}

	#ifdef DEBUG
	    printf("[main] Matriz Original:\n");
		imprimeMatriz(original);
	#endif

	originalLU.tam = n; 
	// alocando a matriz que guardará a fatoração LU
	if(alocaMatrizQuadrada(&originalLU) == -1) {
		fprintf(stderr, "Erro ao alocar a matriz originalLU\n");
		return 0;
	}

	// copia matriz original para a matriz que sofrerá a fatoração LU
	for (int i = 0; i < n*n; ++i)
		originalLU.dados[i] = original.dados[i];
	
	tempo = timestamp();
	fatoracaoLU(&originalLU); // fatora a matriz original em uma LU
	tempo = timestamp() - tempo;
	#ifdef DEBUG
    	printf("[main] Matriz LU:\n");
	#endif
	imprimeMatriz(originalLU); // imprime matriz LU
	printf("# Tempo LU: %.17lf\n", tempo); // imprime tempo levado para calcular LU
	
	if (!(aux = (double*) malloc(n*sizeof(double)))) {
		fprintf(stderr, "Erro ao alocar o vetor auxiliar.\n");
		return 0;		
	}

	inversa.tam = n; 
	// alocando a matriz que guardará a fatoração LU
	if(alocaMatrizQuadrada(&inversa) == -1) {
		fprintf(stderr, "Erro ao alocar a matriz inversa\n");
		return 0;
	} 
	for (int i = 0; i < n; ++i) // inversa inicia como uma matriz identidade
		inversa.dados[pos(i, i, n)] = 1;
	if (substituicao_Lyb(originalLU, &inversa, aux, 1) == -1) { // resolve o sistema L*y=b (o resultado é armazenado na inversa)
		fprintf(stderr, "Erro em substituicao_Lyb.\n");
		return 0;
	}
	if (substituicao_Uxy(originalLU, &inversa, aux) == -1) { // resolve o sistema U*x=y (o resultado é armazenado na inversa)
		fprintf(stderr, "Erro em substituicao_Uxy.\n");
		return 0;
	}
	#ifdef DEBUG
    	printf("[main] Matriz inversa pre-refinamento:\n");
	#endif
	imprimeMatriz(inversa);
	iteracoes = 1;
	// neste ponto, a inversa deveria estar correta... partimos para o refinamento
	if(refinamento(original, &inversa, originalLU, aux, iteracoes) == -1) {
		fprintf(stderr, "Erro em refinamento.\n");
		return 0;
	}

	free(original.dados);
	free(originalLU.dados);
	free(inversa.dados);
	free(arqEntrada);
	free(arqSaida);
	free(aux);
	fclose(out);
	return 0;
}

int fatoracaoLU (MATRIZ *matriz) {
#ifdef DEBUG
	printf("[fatoracaoLU] Iniciando a fatoracao LU.\n");
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
	printf("[fatoracaoLU] Fatoracao LU completa.\n");
#endif 
	return 0;
}

int substituicao_Lyb (MATRIZ L, MATRIZ *y, double *b, int identity) {
#ifdef DEBUG
	printf("[substituicao_Lyb] Iniciando a resolucao do sistema Ly=b.\n");
#endif
	// variavel auxiliar pro tamanho das matrizes
	unsigned int tam = L.tam;

	for (int sl = 0; sl < tam-1; ++sl) { // cada coluna da matriz é um vetor b (A*x=b) para resolver o sistema
		for (int k = 0; k < tam; ++k)
				b[k] = y->dados[pos(k,sl,tam)];
		
		y->dados[pos(0,sl,tam)] = (b[0]*1.0);
		for (int lin = 1; lin < tam; ++lin) { // da segunda linha em diante (a primeira sofre alteração)
			y->dados[pos(lin,sl,tam)] = b[lin];
			for (int col = 0; col < lin; ++col)
				y->dados[pos(lin, sl, tam)] -= L.dados[pos(lin, col, tam)]*y->dados[pos(col, sl, tam)];
		}
	}
#ifdef DEBUG
	 printf("[substituicao_Lyb] Resolucao do sistema Ly=b completa.\n");
#endif 
	return 0;
}

int substituicao_Uxy (MATRIZ U, MATRIZ *y, double *b) {
#ifdef DEBUG
	printf("[substituicao_Uxy] Iniciando a resolucao do sistema Ux=y.\n");
#endif
	// variavel auxiliar pro tamanho das matrizes
	unsigned int tam = U.tam;
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
	printf("[substituicao_Uxy] Resolucao do sistema Ux=y completa.\n");
#endif 
	return 0;
}

int refinamento(MATRIZ A, MATRIZ *inv_A, MATRIZ LU, double *aux, int iter) {
	MATRIZ R;
	unsigned int tam = A.tam;
	R.tam = tam; 
	// alocando a matriz que guardará o residuo
	if(alocaMatrizQuadrada(&R) == -1)
		return -1;

	for (int i = 0; i < iter; ++i) {
		calculaResiduo(A, *inv_A, &R);
		#ifdef DEBUG
	    	printf("[refinamento] Matriz R %d:\n", i+1);
			imprimeMatriz(R);
		#endif

		if (substituicao_Lyb(LU, &R, aux, 1) == -1)
			return -1;
		if (substituicao_Uxy(LU, &R, aux) == -1) 
			return -1;

		for(int j = 0; j < tam*tam; ++j) {
			inv_A->dados[j] += R.dados[j];
		}

		#ifdef DEBUG
	    	printf("[refinamento] Matriz Inversa %d:\n", i+1);
			imprimeMatriz(*inv_A);
		#endif
	}

	free(R.dados);
	return 0;
}

void calculaResiduo(MATRIZ A, MATRIZ inv_A, MATRIZ *R) {
#ifdef DEBUG
	printf("[refinamento] Iniciando refinamento de matrizes %ux%u.\n", A.tam, A.tam);
#endif
	unsigned int tam = A.tam;
	double C, r = 0;
	for (int lin = 0; lin < tam; lin++) {
		for (int col = 0; col < tam; col++) {
			C = 0;
			for (int k = 0; k < tam; k++)
				C += A.dados[pos(lin,k,tam)]*inv_A.dados[pos(k,col,tam)];
			C = (lin == col ? 1.0 - C : -C);
			R->dados[pos(lin, col, tam)] = C; // R = I - A*inv_A
			C *= C;
			r += (lin == col ? 1.0 - C : C); // ||r|| = sum(R[i,j]^2)
		}
	}
	r = sqrt(r); // ||r|| = sqrt(sum(R[i,j]^2))
	printf("r = %.17g\n", r);
}

double timestamp(void){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}