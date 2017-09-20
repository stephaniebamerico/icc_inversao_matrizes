#include "matriz.h"

void fatoracaoLU (MATRIZ *matriz);
void substituicao_Lyb (MATRIZ L, MATRIZ *y);
void troca (MATRIZ *matriz, unsigned int l1, unsigned int l2);
int pivotamentoParcial (MATRIZ *matriz, unsigned int col);
void retrosubstituicao (MATRIZ U, MATRIZ *Y);
void multiply(MATRIZ A, MATRIZ B);

int main (int argc, char const *argv[]) {
    srand( 20172 );

    MATRIZ matriz,origin;
    matriz.tam = 10; // 1 < tam < 32768
    origin.tam = matriz.tam;
    origin.dados = (double*)(malloc (origin.tam*origin.tam*sizeof(double)));
    //matriz.dados = (double*)(malloc (origin.tam*origin.tam*sizeof(double)));



    if(! (matriz.dados = generateSquareRandomMatrix(matriz.tam)) ) {
        fprintf(stderr, "Erro ao alocar a matriz usando generateSquareRandomMatrix.\n");
        return 0;
    }
    for (int i = 0; i < matriz.tam*matriz.tam; ++i)
        origin.dados[i]=matriz.dados[i];
    
     
    fatoracaoLU(&matriz);

    MATRIZ x;
    substituicao_Lyb(matriz, &x);

    printf("x\n");
    imprimeMatriz(x);
    retrosubstituicao(matriz,&x);
    //printf("inv:\n");
    imprimeMatriz(x);
    multiply(origin,x);

    
    return 0;
}

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

void retrosubstituicao (MATRIZ U, MATRIZ *Y)
{

    printf("antes\n");
    imprimeMatriz(*Y);
    unsigned int tam = U.tam;
    double *x ;
    if (!(x = (double*)(calloc (tam, sizeof(double)))))
    {
        printf("deu ruim\n");
        return;
    }
    //double x[U.tam];
    printf("depois\n");
    imprimeMatriz(*Y);

    
    for (int i = 0; i < tam; ++i)
    {
        double soma = 0;
        for (int k = 0; k < tam; ++k)
        {
            x[k] = Y->dados[pos(k,i,tam)];
            Y->dados[pos(k,i,tam)] = 0;
        }
        

        Y->dados[pos(tam-1,i,tam)] = (x[tam-1]*1.0)/U.dados[pos(tam-1, tam-1, tam)];

        for (int k = tam-1; k >= 0; --k)
        {
            soma = x[k];


            for (int j = tam-1; j > k; --j)
            {
                soma -= U.dados[pos(k,j,tam)]*Y->dados[pos(j,i,tam)];
            }
            Y->dados[pos(k,i,tam)]=(soma*1.0)/U.dados[pos(k,k,tam)];
        }

        
    }
    //free(x);

}
/*
int resolveSup (double a[N][N], double x[N], double b[N]) {
    double soma = 0;
    x[N-1] = b[N-1]/a[N-1][N-1];
    for (int k = N-2; k >= 0; --k) {
        soma = b[k];

        for (int j = k; j < N; ++j)
        {
            soma-= a[k][j]*(x[j]);
        }

        
        x[k]=(soma*1.0)/a[k][k];
    }

    
    return 0;
}
*/
void substituicao_Lyb (MATRIZ L, MATRIZ *y) {
    y->tam = L.tam;
    if (!(y->dados = (double *) calloc(y->tam*y->tam, sizeof(double))))
    {
        printf("deu ruim\n");
        return;
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
}

void multiply(MATRIZ A, MATRIZ B)
{
    printf("\n");
    printf("Multiplicando A por X:\n");
    int i, j, k;
    for (i = 0; i < A.tam; i++)
    {
        for (j = 0; j < A.tam; j++)
        {
            double C = 0;
            for (k = 0; k < A.tam; k++)
                C += A.dados[pos(i,k,A.tam)]*B.dados[pos(k,j,B.tam)];
           
            printf("%.0lf ",C );
        }
        printf("\n");
    }
}
