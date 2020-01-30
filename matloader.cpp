#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{   string fname;
    cout<<"load which file?"<<endl;

    getline(cin,fname);
    ifstream fin;
    fin.open(fname.c_str());
    int N;

    fin>>N;

    double **A;
    double *x;
    double *b;

    b = new double[N];
    A = new double*[N];
    for(int i=0; i<N; i++){A[i]=new double[N];}



    for(int row=0; row<N; row++)
    {
        for(int col=0; col<N; col++)
        {
            fin>>A[row][col];
        }

    }

  for(int row=0; row<N; row++)
        {
            fin>>b[row];
        }




    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout<<setw(10)<<A[i][j];
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    for(int i=0; i<N; i++)
    {
        cout<<b[i]<<" ";
    }
 return 0;
}