//Not recommended for health reasons...
#include <iostream>
using namespace std;

void Shoot(double vector[]){
    for(int index = 2; index < 6; index++)
    {
        vector[index]= -20 + (2*vector[index-1]) -  vector[index-2];
    }

}

void Print(double vector[]){
    for(int i=0; i<6; i++)
    {
        cout<<"["<<i<<"] = "<<vector[i]<<endl;
    }
}

void ShootingMethod(){
    double C;
    double error, correction, dx;
    double xsol[6], x[6];
    dx = 1.0/(5);
    xsol[0] = 100;
    xsol[1] = 84;

    Shoot(xsol);

    cout << " Actual XSol" << endl;
    Print(xsol);

    x[0]=0.0;
    x[1]=1.0;

    Shoot(x);

    cout << "X" << endl;
    Print(x);

    C = x[5];

    cout<<"influence of x[1]=1.0 at x[5],  C = "<<C<<endl;
    cout<<"Guessing x[1] = 60"<<endl;
    x[0]=100;  ///reset the boundary condition
    x[1]=60;   ///just a random guess..

    Shoot(x);

    cout<<"solution based on Guess = 60"<<endl;
    Print(x);

    error = (xsol[5]-x[5])*dx;
    cout<<"for ref: Error based on x[1] = 60, error = "<<error<<endl;

    x[1] = x[1]+error;
    Shoot(x);
    cout<<" computed solution:"<<endl;
    Print(x);


}




int main()
{
/// x0 = 100, x5 = 20
/// 1 -2 1 => -20
/// actual solution 100, 84, 48, 8,  -84, -180


    ShootingMethod();
}
