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

    double **A,**L;
    double *x;
    double *b, *y;
    double d, sum;
    x = new double[N];
    b = new double[N];
    y = new double[N];
    A = new double*[N];
    L = new double*[N];

    for(int i=0; i<N; i++){A[i]=new double[N];}
    for(int i=0; i<N; i++){L[i]=new double[N];}

    ///fill A matrix
    for(int row=0; row<N; row++)
    {
        for(int col=0; col<N; col++)
        {
            fin>>A[row][col];
        }
    }
    for(int col=0; col<N; col++)
    {
        L[N-1][N-(col+1)] = A[0][col];
    }
    ///fill up b and set to last column in matrix
    for(int row=0; row<N; row++)
    {
            fin>>b[row];
    }


    cout<<"A before upper triangular."<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
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
        for(int col = k; col<N; col++)
        {
            temp = A[k][col];
            A[k][col] = A[maxRow][col];
            A[maxRow][col] = temp;
        }

		///divide A(row j) by max; {yields 1.0 on diag}
		for(int col = k; col<N; col++)
        {
		    A[k][col] = A[k][col]/maxValu;
        }

        ///convert matrix to upper triangular
        for(int i=k+1; i<N; i++)
        {
            double m = A[i][k];
            A[i][k] = A[i][k]/A[k][k];
            L[i-1][k] = A[i][k];
            for(int j = k; j<N; j++)
            {
                A[i][j] = A[i][j] - (m*A[k][j]);
            }
        }
    }


	cout<<"U after triangulation: "<<endl;
	for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout<<setw(12)<<A[i][j];
        }
        cout<<endl;
    }cout<<endl;

    cout<<"L after triangulation: "<<endl;
	for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout<<setw(12)<<L[i][j];
        }
        cout<<endl;
    }cout<<endl;




    ///FORWARD SOLVE: LY = B
    y[0] = b[0]/L[0][0];
    for (int k = 1; k<N; k++)
    {
          double total = 0.0;
          for(int j = 0;j<=k-1;j++)
          {
              total = total + L[k][j]*y[j];
          }
          y[k] = (b[k]-total)/L[k][k];
    }

    ///BACKSOLVE: UX = Y
    x[N-1] = y[N-1]/A[N-1][N-1];
    for (int k = N-2; k >=0; k--)
    {
          double total = 0.0;
          for(int j = k+1;j<=N-1;j++)
          {
              total = total + A[k][j]*x[j];
          }
          x[k] = (y[k]-total)/A[k][k];
    }

    cout<<"Solution vector"<<endl;
    for (int i=0; i<N; i++)
    {
            cout<<setw(8)<<x[i];
    }



return 0;
}
