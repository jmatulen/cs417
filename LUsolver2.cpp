#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

int main()
{

    int N;
    cout<<"size of solution?"<<endl;
    cin>>N;

    double **A, **L, **U;
    double *x;
    double *xnew;
    double *b, *y;
    double error, d, sum, xsum, xnewSum;

    x = new double[N];///solution vector: Ux = y
    b = new double[N];///given b vector
    y  = new double[N];///y vector for: Ly = b
    A = new double*[N];///Given system matrix
    L = new double*[N];///Lower triangular of A
    U = new double* [N];/// Upper triangular of A

    for(int i=0; i<N; i++){A[i]=new double[N];}
    for(int i=0; i<N; i++){L[i]=new double[N];}
    for(int i=0; i<N; i++){U[i]=new double[N];}

    default_random_engine gen(time(NULL));
    uniform_real_distribution<double> rdist(-100.0, 100.0);

    for(int row=0; row<N; row++)
    {   d=0.0;
        for(int col=0; col<N; col++)
        {
            L[row][col] = 0;
            U[row][col] = 0;
            A[row][col]=rdist(gen);
            d = d + fabs(A[row][col]);
        }
        A[row][row]=d;
    }

    for(int i=0; i<N; i++)
    {
        x[i]=i+1;
    }

    ///matvec A * x -> b
    for(int row=0; row<N; row++)
    {
        sum=0.0;
        for(int col=0; col<N; col++)
        {
            sum = sum + A[row][col]*x[col];
        }
        b[row]=sum;
    }
    ///set up L and U matrices
    for(int i=0; i<N; i++)
    {
        U[0][i] = A[0][i];/*set first row of U to first row of A.
                          ******************************************************
                          * If A=LU, and L(0,*) = |1 0 0 ... 0|                *
                          *                                                    *
                          * and U(*,0) = |u(0,0)                               *
                          *              |0                                    *
                          *              |0                                    *
                          *              |.                                    *
                          *              |.                                    *
                          *              |.                                    *
                          *              |0                                    *
                          *                                                    *
                          * and since L(0,0) = 1                               *
                          * then L(0,0)*U(0,0) = 1*U(0,0) = A(0,0),            *
                          * therefore U(0,0) == A(0,0)                         *
                          * It follows that the first row of U is equal to A's *                                                *
                          ******************************************************/
        L[i][i] = 1;///Set diagonal of L to 1
    }

    ///compute U and L
    sum = 0.0;

    for(int k = 0; k<N; k++)
    {

        for(int m=k; m<N; m++)
        {
            for(int j = 0; j<k-1; j++)
            {
                sum = sum + (L[k][j]*U[j][m]);
            }
            U[k][m] = A[k][m] - sum;
        }
        for(int i = k+1; i<N; i++)
        {
            for(int j = 0; j<=k-1; j++)
            {
                sum = sum + (L[i][j]*U[j][k]);
            }
            L[i][k] = (A[i][k] - sum)/U[k][k];
        }
    }

    ///forward substitution: Ly = b
    y[0] = b[0];

    for(int i = 1; i<N; i++)
    {
        for(int j = 0; j<i; j++)
        {
            sum = sum + L[i][j] * y[j];
        }
        y[i] = (b[i] - sum);
    }


    x[N-1] = y[N-1];
    for(int i = N-2; i>N; i--)
    {
        for(int j = N-1; j>i; j--)
        {
            sum = sum + U[i][j] * y[j];
        }
        cout<<endl<<endl<<"ljfada"<<endl<<endl;
        x[i] = (b[i] - sum);
    }

    cout<<"L"<<endl;
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<N; j++)
        {
            cout<<setw(10)<<L[i][j];
        }cout<<endl;
    }

    cout<<"U"<<endl;
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<N; j++)
        {
            cout<<setw(10)<<U[i][j];
        }cout<<endl;
    }

    for(int i = 0; i<N; i++)
    {
        cout<<setw(10)<<x[i];
    }
return 0;
}
