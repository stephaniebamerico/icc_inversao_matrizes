#include <stdio.h>
#define N 3
int troca (double a[N][N], int j, int k)
{
    double aux;
    for (int i = 0; i < N; ++i)
    {
        aux = a[j][i];
        a[j][i] = a[k][i];
        a[k][i]=aux;
    }
}

void elimina (double a[N][N], double b[N])
{
    double m;
    for (int k = 0; k < N-1; ++k)
    {

        int i;
        for (i = k; i < N, a[i][k]== 0; ++i);
            if ( k != i) troca (a,i,k);
            for (i = k+1; i < N; ++i)
            {
                m = (a[i][k]*1.0)/a[k][k];
                b[i]-=m*b[k];
                for (int j = k; j < N; ++j)
                        a[i][j]-=m*a[k][j];
            }

    }
    for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
               printf("%.1lf ",a[i][j] );
            }
            printf("     %.1lf \n",b[i] );
        }    
}

int resolve (double a[N][N], double x[N], double b[N])
{
    double soma = 0;
    x[N-1] = b[N-1]/a[N-1][N-1];
    for (int k = N-2; k >= 0; --k)
    {
        soma = b[k];
        for (int j = k; j < N; ++j)
        {
            soma-= a[k][j]*(x[j]);
        }
        x[k]=(soma*1.0)/a[k][k];
    }
    for (int i = 0; i < N; ++i)
    {
        printf("%.20lf \n",x[i] );
    }
    return 0;
}


int main(int argc, char const *argv[])
{
    double a[N][N] ={1, -1, 2, 
                    2, 1, -1, 
                    -2, -5, 3},
      b[N] = {2, 1, 3},
      x[N];

    elimina(a,b);

    resolve(a,x,b);

    return 0;
}