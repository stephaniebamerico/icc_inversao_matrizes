#include <stdio.h>
#define N 3
int troca (double a[N][N], int j, int k) {
    double aux;
    for (int i = 0; i < N; ++i) {
        aux = a[j][i];
        a[j][i] = a[k][i];
        a[k][i]=aux;
    }
}

void elimina (double a[N][N], double l[N][N], double u[N][N] ) {
    double m;
    for (int k = 0; k < N-1; ++k) {
        int i;
        for (i = k; i < N, a[i][k] == 0; ++i);
            if ( k != i) troca (a,i,k);
            
            for (i = k+1; i < N; ++i) {
                m = (a[i][k]*1.0)/a[k][k];
                for (int j = k; j < N; ++j)
                        a[i][j] -= m*a[k][j];
                a[i][k] = m;
            }
    }
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i<j)
            {
                u[i][j]=a[i][j];
                l[i][j]=0;
            }
            else if (i == j)
            {
                l[i][j]=1;
                u[i][j]=a[i][j];
            }
            else
            {
                l[i][j]=a[i][j];
                u[i][j]=0;
            }
        }
    }
}

int resolve (double a[N][N], double x[N], double b[N]) {
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
        //if (x[i] >= 0) printf(" ");
        //printf("%.20lf \n", x[i]);
    }
    
    return 0;
}


int main(int argc, char const *argv[]) {
    double a[N][N] = { 1, 0,  2, 
                       2,  -1, 3, 
                      4, 1,  8},
      b[N] = {2, 1, 3};
      double x1[N],x2[N],x3[N];
      double y1[N],y2[N],y3[N];
      double l[N][N], u[N][N];

    elimina(a,l,u);
    b[0] = 1;
    b[1] = 0;
    b[2] = 0;
    resolve(l,y1,b);
    b[0] = 0;
    b[1] = 1;
    b[2] = 0;
    resolve(l,y2,b);
    b[0] = 0;
    b[1] = 0;
    b[2] = 1;
    resolve(l,y3,b);
    
    resolve(u,x1,y1);
    resolve(u,x2,y2);
    resolve(u,x3,y3);

    for (int i = 0; i < N; ++i)
    {
        printf("%.1lf %.1lf %.1lf\n",x1[i],x2[i],x3[i] );
    }


    return 0;
}