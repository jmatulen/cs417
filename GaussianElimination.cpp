#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <ctime>
#include <iomanip>
using namespace std;

int main()
{

    //cout.precision(4);        //set precision
    //cout.setf(ios::fixed);
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


    ///fstream fout;
    ///fout.open("matdata.txt",ios::out);
    ///fout<<N<<endl;
    cout<<"A before upper triangular."<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout<<setw(8)<<A[i][j];
        }
        cout<<endl<<endl;
    }
    for(int i=0; i<N; i++)
    {
        cout<<setw(8)<<b[i];
    }
    cout<<endl;
    cout <<"b :"<<endl;
    for (int i=0; i<N; i++)
            printf("%lf\n", b[i]);

    for(int j = 0; j<N; j++) ///columns of A
	{	int maxRow = j;
		double maxValu = A[j][j];

		///compare with all rows below in that column
		for(int i=j; i<N; i++)
        {

		    if(fabs(A[i][j])>maxValu)
            {
		       maxValu = A[i][j];
	     	   maxRow = i;
		    }
		}

        double temp = 0.0;
        for(int col = j; col<N; col++)
        {
            temp = A[j][col];
            A[j][col] = A[maxRow][col];
            A[maxRow][col] = temp;
        }
        temp = b[j];
        b[j] = b[maxRow];
        b[maxRow] = temp;


		///divide A(row j) by max; {yields 1.0 on diag}
		for(int col = j; col<N; col++)
        {
		    A[j][col] = A[j][col]/maxValu;
		    ///divide b[j] by max
        }
         b[j] = b[j]/maxValu;

            for(int k=j+1; k<N; k++) ///row under j
            {
                for(int i=j; i<N; i++)
                {
                    A[k][i] =  A[k][i] + (-1.0*A[k][j]*A[j][i]);
                }
                b[k] = b[k] + (-1.0*A[k][j]*b[j]);
           }
        }


	cout<<"A after triangulation: "<<endl;
	for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout<<setw(12)<<A[i][j];
        }
        cout<<endl;
    }
    cout <<"b :"<<endl;
    for (int i=0; i<N; i++)
            printf("%lf\n", b[i]);


    printf("\nSolution for the system, before:\n");
        for (int i=0; i<N; i++)
            printf("%lf\n", x[i]);


    ///backsolve

    for (int k = N-1; k > 0; k--)
    {
          cout<<"gibber"<<endl;
          double total = 0.0;
          for(int j = k+1;j>N-1;j--)
          {
              cout<<"jabber"<<endl;
              total = total + A[k][j]*x[j];
          }
          x[k] = (b[k]-total)/A[k][k];

    }

        printf("\nSolution for the system:\n");
        for (int i=0; i<N; i++)
            printf("%lf\n", x[i]);



return 0;
}

