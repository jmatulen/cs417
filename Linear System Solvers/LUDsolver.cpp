///////////////////////////////////////////////////////////////////
/// File: LUDsolver.cpp                                           //
/// Author: Joshua Matulenas                                     //
///                                                              //
///                                                              //
/// Description: Program solves a system of equations            //
///              Using LU Decomposition. The Matrix A is         //
///              "decomposed" into an Upper Triangular matrix U, //
///              and a Lower Triangular matrix L. Using the eqn. //
///              [A] --> [L][U], solving for Ax = b can be       //
///              formulated as Ly = b, and Ux = y. Initially,    //
///              if we start by solving for y, by using the      //
///              given b and computed L and forward substituting,//
///              we can use this y in Ux = y to solve for x by   //
///              back substitution. This algorithm assumes matrix//
///              A is non-singular, and therefore doesn't have   //
///              pivoting capabilities.                          //
///                                                              //
///////////////////////////////////////////////////////////////////

#include <iostream> ///i/o
#include <cmath>    ///used for fabs()
#include <fstream>  ///required for file i/o
#include <string>   ///required for "fname.c_str()"
#include <iomanip>  ///required for setw()

using namespace std;

int main()
{
    string fname; ///file to be read in to build A matrix and b vector
    cout<<"load which file?"<<endl;

    getline(cin,fname);
    ifstream fin;
    fin.open(fname.c_str());
    int N;

    fin>>N;

    double **A;
    double *x;
    double *b;
    double d, sum;

    x = new double[N];
    b = new double[N];
    A = new double*[N];

    for(int i=0; i<N; i++){A[i]=new double[N];}

    ///fill A matrix
    for(int row=0; row<N; row++)
    {
        for(int col=0; col<N; col++)
        {
            fin>>A[row][col];
        }
    }

    ///fill up b and set to last column in matrix
    for(int row=0; row<N; row++)
    {
            fin>>b[row];
    }


    ///decompose A --> LU
    for(int k = 0; k<N-1; k++){
        for(int i = k+1; i<N; i++){
            double m = A[i][k]/A[k][k];
            A[i][k] = m;

            for(int j = k+1; j<N; j++){
                A[i][j] = A[i][j] - m*A[k][j];
            }
        }
    }



    cout<<setw(12)<<"A decomposed into U and L"<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout<<setw(12)<<A[i][j];
        }
        cout<<endl<<endl;
    }



    ///forward substitution
    for(int i=1; i<N; i++)
    {
        sum = b[i];
        for(int j=0; j<=i-1; j++)
        {
            sum = sum - A[i][j]*b[j];
        }
        b[i] = sum;
    }

    ///back substitution
    x[N-1] = b[N-1]/A[N-1][N-1];
    for(int i=N-2; i>=0; i--)
    {
        sum = 0.0;
        for(int j=i+1; j<N; j++)
        {
            sum = sum + A[i][j]*x[j];
        }
        x[i]=(b[i]-sum)/A[i][i];
    }

    cout<<"X vector"<<endl;
    for(int i=0; i<N; i++)
    {
        cout<<endl<<x[i];
    }
    cout<<endl;

return 0;
}
