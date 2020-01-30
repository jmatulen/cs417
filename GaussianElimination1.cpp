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

    for(int j = 0; j<N; j++) ///columns of A
	{	int maxRow = j;
		double max = A[j][j];

		///compare with all rows below in that column
		for(int i=j; i<N; i++)
        {

		    if(fabs(A[i][j])>max)
            {
		       max = A[i][j];
	     	   maxRow = i;
		    }
		}

    		//if (maxRow!=j)
            //{
    		    double temp = 0.0;
    		    for(int col = j; col<N; col++)
                {
        			temp = A[j][col];
        			A[j][col] = A[maxRow][col];
        			A[maxRow][col] = temp;
        			temp = b[j];
        			b[j] = b[maxRow];
        			b[maxRow] = temp;
    		    }
		    //}

		///divide A(row j) by max; {yields 1.0 on diag}
		for(int col = j; col<N; col++)
        {
		    A[j][col] = A[j][col]/max;
		    ///divide b[j] by max
		    b[j] = b[j]/max;


            for(int k=j+1; k<N; k++) ///row under j
            {
                //double val = A[k][j];
                for(int i=j; i<N; i++)
                {
                    A[k][i] =  A[k][i] + (-1.0*A[k][j]*A[j][i]);
                }
                
                b[k] = b[k] + (-1.0*A[k][j]*b[j]);

           }
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
    cout <<"b :"<<b[N-1]<<endl;
	
    
    printf("\nSolution for the system, before:\n");
        for (int i=0; i<N; i++)
            printf("%lf\n", x[i]);
    
    
    ///backsolve 
    x[N-1] = b[N-1];
    for (int i = N-2; i > 0; i--)
    {   
          cout<<"gibber"<<endl;
          double total = 0.0;
          for(int j= i+1;j>=N-1;j--)
          { 
              cout<<"jabber"<<endl;
              total = total + A[i][j]*x[j];
          }
          x[i] = b[i]-total;

    }

        printf("\nSolution for the system:\n");
        for (int i=0; i<N; i++)
            printf("%lf\n", x[i]);



return 0;
}
