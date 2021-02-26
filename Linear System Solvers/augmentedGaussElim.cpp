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
    double *x;
    double *b;
    double d, sum;
    x = new double[N];
    b = new double[N];
    A = new double*[N];

    for(int i=0; i<N; i++){A[i]=new double[N+1];}///create (N,N+1) matrix to make room for b column

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
            A[row][N] = b[row];///augmenting matrix by setting last column to b vector
    }


    cout<<"A before upper triangular."<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N+1; j++)
        {
            cout<<setw(10)<<A[i][j];
        }
        cout<<endl<<endl;
    }
    for(int i=0; i<N; i++)
    {
        cout<<setw(8)<<b[i];
    }
    cout<<endl;

    ///start forward elimination
    for (int k = 0; k<N; k++)
    {
        int maxRow = k;///variable to store row index of maximum value in column
	double maxValu = A[k][k];///variable to store maximum value in column

	///search for max value in current column, store row index
	for(int i=k; i<N; i++)
       	{
	    if(fabs(A[i][k])>maxValu)
            {
	       	maxValu = A[i][k];
	       	maxRow = i;
	    }
	}

        double temp = 0.0;///holds value to be swapped with value in maxRow
        for(int col = k; col<N+1; col++)
        {
            temp = A[k][col];
            A[k][col] = A[maxRow][col];
            A[maxRow][col] = temp;
        }

	///divide A(row j) by max; {yields 1.0 on diag}
	for(int col = k; col<N+1; col++)
        {
	    A[k][col] = A[k][col]/maxValu;
        }

        ///convert matrix to upper triangular
        for(int i=k+1; i<N; i++) 
        {
            double m = A[i][k];
            A[i][k] = A[i][k]/A[k][k];
            for(int j = k; j<N+1; j++)
            {
                A[i][j] = A[i][j] - (m*A[k][j]);
            }
        }
    }


    cout<<"A after triangulation: "<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N+1; j++)
        {
            cout<<setw(12)<<A[i][j];
        }
        cout<<endl;
    }cout<<endl;

    ///backsolve
    x[N-1] = A[N-1][N];
    for (int k = N-2; k >=0; k--)
    {
         double total = 0.0;
         for(int j = k+1;j<=N-1;j++)
         {
             total = total + A[k][j]*x[j];
         }
         x[k] = (A[k][N]-total);
    }

    cout<<"Solution vector"<<endl;
    for (int i=0; i<N; i++)
    {
         printf("%lf\n", x[i]);
    }
    return 0;
}

