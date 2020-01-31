#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double fx(double x);
double fPrimex(double x);
int main()
{
    double d, error = 100.0, x = 0.0;
    int i = 1;
    cout<<"Initial guess for x?"<<endl;
    cin >> d;
    cout<<"Iterations"<<setw(11)<<"Error"<<endl;
    while(error>.00001)
    {
        x = d -(fx(d)/fPrimex(d));
        error = fabs(fx(x));
        cout<<left<<setw(10)<<i<<right<<setw(11)<<error<<endl;
        i++;
        d = x;
    }

    return 0;
}

///initialize function. *4cos(x) +e^7x + 4x^2 = 0*
double fx(double n)
{
    double x = pow(n,3.0)-cos(n);
    return x;
}
///calculate derivative of function
double fPrimex(double n)
{
    double x = 3.0*pow(n,2.0)+sin(n);
    return x;
}
