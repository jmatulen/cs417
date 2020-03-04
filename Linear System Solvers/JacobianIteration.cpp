#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    string fname;
    cout<<"load which file?"<<endl;

    getline(cin,fname);
    ifstream fin;
    fin.open(fname.c_str());
    int N;

    fin>>N;

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

    ///fill A matrix
    for(int row=0; row<N; row++)
    {
        for(int col=0; col<N; col++)
        {
            fin>>A[row][col];
        }

    }
    ///fill up b 
    for(int row=0; row<N; row++)
    {
            fin>>b[row];
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
    cout<<"Error"<<endl;
    while(error>.00000001)
    {   
        for(int i=0; i<N; i++)
        {
            x[i]= xnew[i];///reset xold values with xnew values
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
        }cout<<error<<endl;
    }cout<<"Soultion Vector: ";for(int i = 0; i<N; i++){cout<<xnew[i]<<"  ";}
return 0;
}
