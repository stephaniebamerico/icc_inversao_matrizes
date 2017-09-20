#include "matriz.h"
#include <string.h>

void fatoracaoLU (MATRIZ *matriz);
int pivotamentoParcial (MATRIZ *matriz, unsigned int col);
int substituicao_Lyb (MATRIZ L, MATRIZ *y);
int substituicao_Uxy (MATRIZ U, MATRIZ *Y);
void multiplicaMatrizes(MATRIZ A, MATRIZ B);

int main (int argc, char const *argv[]) {
    srand( 20172 );

    MATRIZ matriz,origin,x;
    matriz.tam = 10; // 1 < tam < 32768
    origin.tam = matriz.tam;
    


    if(! (matriz.dados = generateSquareRandomMatrix(matriz.tam)) ) {
        fprintf(stderr, "Erro ao alocar a matriz usando generateSquareRandomMatrix.\n");
        return 0;
    }
    if (! (origin.dados = (double*)malloc (origin.tam*origin.tam*sizeof(double))))
    {
        fprintf(stderr, "Erro ao alocar a matriz\n");
        return 0;
    }
    //copia matriz pra matriz original
    for (int i = 0; i < matriz.tam*matriz.tam; ++i)
        origin.dados[i]=matriz.dados[i];
    
     
    fatoracaoLU(&matriz);
    //funções retornam 0 se malloc falhar   
    if (!substituicao_Lyb(matriz, &x))
        return 0;
    if (!substituicao_Uxy(matriz, &x))
        return 0;

    multiplicaMatrizes(origin,x);

    
    return 0;
}

/*==============================*/
/*FUNÇÕES NÃO UTILIZADAS NA MAIN*/
/*==============================*/
void troca (MATRIZ *matriz, unsigned int l1, unsigned int l2);

void fatoracaoLU (MATRIZ *matriz) {
    double m;
    for (int col = 0; col < matriz->tam-1; ++col) {
        //pivotamentoParcial(matriz, col);            
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

int substituicao_Uxy (MATRIZ U, MATRIZ *Y)
{
    //variavel auxiliar pro tamanho das matrizes
    unsigned int tam = U.tam;
    //vetor auxiliar 
    double *b ;
    //aloca memória para o vetor X
    if (!(b = (double*)(calloc (tam, sizeof(double)))))
    {
        fprintf(stderr,"Erro ao alocar vetor auxiliar X na retrosubstituição\n");
        return 0;
    }
    //i é a coluna da matriz na qual estamos realizando a substituição
    for (int i = 0; i < tam; ++i)
    {
        //Y será alterado diretamente, funcionando como x em Ax = b
        //A coluna de Y é copiada para o vetor b
        for (int k = 0; k < tam; ++k)
            b[k] = Y->dados[pos(k,i,tam)];
        //faz a retrosubstituição 
        Y->dados[pos(tam-1,i,tam)] = (b[tam-1]*1.0)/U.dados[pos(tam-1, tam-1, tam)];
        for (int k = tam-1; k >= 0; --k)
        {
            Y->dados[pos(k,i,tam)] = b[k];
            for (int j = tam-1; j > k; --j)
                Y->dados[pos(k,i,tam)] -= U.dados[pos(k,j,tam)]*Y->dados[pos(j,i,tam)];
            Y->dados[pos(k,i,tam)]=(Y->dados[pos(k,i,tam)]*1.0)/U.dados[pos(k,k,tam)];
        }

        
    }
    return 1;
}

int substituicao_Lyb (MATRIZ L, MATRIZ *y) {
    y->tam = L.tam;
    if (!(y->dados = (double *) calloc(y->tam*y->tam, sizeof(double))))
    {
        fprintf(stderr,"Erro ao alocar matriz Y na substituição progressiva\n");
        return 0;
    }


    for (int i = 0; i < y->tam; ++i) // inicia como uma matriz identidade
        y->dados[pos(i, i, y->tam)] = 1;

    for (int b = 0; b < y->tam-1; ++b) { // cada coluna da matriz é um vetor b para resolver o sistema
        for (int lin = 1; lin < y->tam; ++lin) { // da segunda linha até até a diagonal principal
            for (int col = b; col < lin; ++col) { // começa a partir da primeira valoração não nula (b)
                y->dados[pos(lin, b, y->tam)] -= L.dados[pos(lin, col, L.tam)]*y->dados[pos(col, b, y->tam)];
            }
        }
    }
    return 1;
}

void multiplicaMatrizes(MATRIZ A, MATRIZ B)
{
    printf("Multiplicando A por X:\n");
    int i, j, k;
    for (i = 0; i < A.tam; i++)
    {
        for (j = 0; j < A.tam; j++)
        {
            double C = 0;
            for (k = 0; k < A.tam; k++)
                C += A.dados[pos(i,k,A.tam)]*B.dados[pos(k,j,B.tam)];
           
            printf("%s%.0lf ",C>=0?" ":"",C );
        }
        printf("\n");
    }
}
