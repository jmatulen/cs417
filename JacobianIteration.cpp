#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

int main()
{

    int N;
    cout<<"size of solution?"<<endl;
    cin>>N;

    double **A;
    double **D;
    double *x;
    double *xnew;
    double *b;
    double error, d, sum;
    xnew = new double[N];
    x = new double[N];
    b = new double[N];
    A = new double*[N];
    D = new double*[N];
    for(int i=0; i<N; i++){A[i]=new double[N];}
    for(int i=0; i<N; i++){D[i]=new double[N];}

    default_random_engine gen(time(NULL));
    uniform_real_distribution<double> rdist(-100.0, 100.0);

    for(int row=0; row<N; row++)
    {   d=0.0;
        for(int col=0; col<N; col++)
        {
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
    ///set up D, xnew and A matrices
    for(int i=0; i<N; i++)
    {
            D[i][i]=1.0/A[i][i];
            A[i][i]=0;
            xnew[i]= b[i];
    }

    ///compute first soln matrix using initial guess
    error = 1.0;
    while(error>.00000001)
    {
        for(int i=0; i<N; i++)
        {
            x[i]= xnew[i];
        }
        for(int i=0; i<N; i++)
        {
            sum = 0.0;
            for(int j = 0; j<N; j++)
            {
                sum = sum + (A[i][j]*x[j]); 
            }
            xnew[i] = D[i][i]*(b[i]-sum);
            error = fabs(xnew[i]-x[i]);
            cout<<error<<endl;
        }
    }
}