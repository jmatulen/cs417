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
    double *x;
    double *b;
    double d, sum;
    x = new double[N];
    b = new double[N];
    A = new double*[N];
    for(int i=0; i<N; i++){A[i]=new double[N];}

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

    fstream fout;
    fout.open("matdata.txt",ios::out);
    fout<<N<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            fout<<A[i][j]<<" ";
        }
        fout<<endl;
    }
    for(int i=0; i<N; i++)
    {
        fout<<b[i]<<" ";
    }
    fout<<endl;
}
