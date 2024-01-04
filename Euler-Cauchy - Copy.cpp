//Euler-Cauchy, Heun and Runge-Kutta Methods
#include<iostream>
#include<cmath>
#include<graphics.h>
#include<iomanip>

using namespace std;

double h[]={0.5, 0.2, 0.1, 0.05, 0.02, 0.01};// create an array for h

double f(double x, double y){
    return -x*y;
}//the given function

double AV(double x){
    return exp(-x*x/2.0);
}//the actual value (derived analytically)

double euler_y(double x, double h){
    double y_n=1.0; //y(0)=1
    double n=x/h;
    for (int i=0; i<n; i++){
        y_n+=h*f(i*h,y_n);// notice that x_n=h*n;
    }
    return y_n;
}//y using euler-cauchy

double heun(double x, double h){
    double y_n=1.0;
    double n=x/h;
    double y_aux;
    for (int i=0; i<n; i++){
        y_aux=y_n+h*f(i*h,y_n);
        y_n+=0.5*h*(f(i*h,y_n)+f((i+1)*h,y_aux));
    }
    return y_n;
}// y using Heun

double runge(double x, double h){
    double y_n=1.0;
    double n=x/h;
    double k1,k2,k3,k4;
    for (int i=0; i<n; i++){
        k1=h*f(i*h,y_n);
        k2=h*f(i*h+0.5*h, y_n+0.5*k1);
        k3=h*f(i*h+0.5*h, y_n+0.5*k2);
        k4=h*f(i*h+h, y_n+k3);
        y_n+=1.0/6*(k1+2.0*k2+2.0*k3+k4);
    }
    return y_n;
}//y using Runge-Kutta

int main(){
    //these are all formatting stuff
    cout<<"\t"<<"Euler-Cauchy"<<"\t\t"<<"Heun"<<"\t\t\t\t"<<"Runge-Kutta"<<endl;
    cout<<"h\t"<<"AV-y(1)"<<"\t"<<"AV-y(3)"<<"\t\t"<<"AV-y(1)"<<"\t\t"<<"AV-y(3)"<<"\t\t"<<"AV-y(1)"<<"\t\t"<<"AV-y(3)"<<endl;
    for(int i=0; i<6; i++){
       cout<<h[i]<<setprecision(3)<<"\t"<<fabs(AV(1.0)-euler_y(1.0,h[i]))<<"\t"<<fabs(AV(3.0)-euler_y(3.0,h[i]))
       <<"\t";
       if (i<4) cout<<"\t"; //this is just a formatting thing
       cout<<fabs(AV(1.0)-heun(1.0,h[i]))<<"\t";
       if (i==0) cout<<"\t";
       cout<<fabs(AV(3.0)-heun(3.0,h[i]))<<"\t";
       if (i<2) cout<<"\t";
       cout<<fabs(AV(1.0)-runge(1.0,h[i]))<<"\t";
       if (i==1) cout<<"\t";
       cout<<fabs(AV(3.0)-runge(3.0,h[i]))<<endl;
    }
    return 0;
}
