//numerical differentiation
#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

double AV= 3.0-cos(1);//the actual value

double f(double x){
    return x*x*x-sin(x);
}//define the f(x)

double twoPointLeft(double h){
    return (f(1+h)-f(1))/h;
}//2-point left

double twoPointRight(double h){
    return (f(1)-f(1-h))/h;
}//2-point Right

double threePoint(double h){
    return (f(1+h)-f(1-h))/(2*h);
}//3-point

double fourPointPos(double h){
    return (-2*f(1-h)-3*f(1)+6*f(1+h)-f(1+2*h))/(6*h);
}//4-point Positive

double fourPointNeg(double h){
    return (-2*f(1+h)-3*f(1)+6*f(1-h)-f(1-2*h))/(-6*h);
}//4-point Negative

double fivePoint(double h){
    return (f(1-2*h)-8*f(1-h)+8*f(1+h)-f(1+2*h))/(12*h);
}//5-point

int main(){
	cout<<"Table of Errors for the First Derivative of x^3 - sin x"<<endl;
    cout<<"Actual Value = "<<setprecision(10)<<AV<<endl;
    cout<<"\t\t\th=0.01\t\t\th=0.001"<<endl;
    cout<<"2-Point Left\t\t"<<setprecision(10)<<fabs(twoPointLeft(0.01)-AV)<<"\t\t"<<fabs(twoPointLeft(0.001)-AV)<<endl;
    cout<<"2-Point Right\t\t"<<setprecision(10)<<fabs(twoPointRight(0.01)-AV)<<"\t\t"<<fabs(twoPointRight(0.001)-AV)<<endl;
    cout<<"3-Point\t\t\t"<<setprecision(10)<<fabs(threePoint(0.01)-AV)<<"\t\t"<<fabs(threePoint(0.001)-AV)<<endl;
    cout<<"4-Point Positive\t"<<setprecision(10)<<fabs(fourPointPos(0.01)-AV)<<"\t"<<fabs(fourPointPos(0.001)-AV)<<endl;
    cout<<"4-Point Negative\t"<<setprecision(10)<<fabs(fourPointNeg(0.01)-AV)<<"\t"<<fabs(fourPointNeg(0.001)-AV)<<endl;
    cout<<"5-Point\t\t\t"<<setprecision(10)<<fabs(fivePoint(0.01)-AV)<<"\t"<<fabs(fivePoint(0.001)-AV)<<endl;
    return 0;
}
