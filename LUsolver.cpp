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
        L[i][0] = A[i][0];///set first column of L to first column of A
        U[i][i] = 1;///Set diagonal of U to 1
    }

    ///compute U and L
    sum = 0.0;
    for(int i = 1; i<N; i++)
    {

        for(int j=1; j<=i; j++)
        {
            for(int k = 0; k<=j-1; j++)
            {
                sum = sum + (L[i][k]*U[k][j]);
            }
            L[i][j] = A[i][j] - sum;
        }
        for(int j = i+1; j<N; j++)
        {
            for(int k = 0; k<=i-1; k++)
            {
                sum = sum + (L[i][k]*U[k][j]);
            }
            U[i][j] = (A[i][j] - sum)/L[i][i];
        }
    }
    /*
    ///forward substitution: Ly = b --> y = b/L
    y[0] = b[0]/A[0][0];
    for(int i = 1; i<N; i++)
    {
        y[i] = (b[i] - )
    }*/
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
return 0;
}
