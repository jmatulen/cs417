#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

int main()
{

    int N;
    double w;
    cout<<"size of solution?"<<endl;
    cin>>N;
    cout<<"size of omega?"<<endl;
    cin>>w;

    double **A;
    double **D;
    double *x;
    double *xnew;
    double *b;
    double error, d, sum, xsum, xnewSum;
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
            xsum = 0.0;
            xnewSum = 0.0;
            for(int j = 0; j<i; j++)
            {
                xsum = xsum + (A[i][j]*x[j]); 
            }
            for(int j = i; j<N; j++)
            {
                xnewSum = xnewSum + (A[i][j]*xnew[j]);
            }
            xnew[i] =((1-w)*x[i])+((w*D[i][i])*(b[i]-xsum-xnewSum));
            error = -1.0*(xnew[i]-x[i]);
            error = error*error;
            cout<<error<<endl;
        }
    }
}