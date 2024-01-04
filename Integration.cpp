//numerical integration
#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

double AV=1-sin(4)/4;//actual value

double f(double x){
    return sin(x)*sin(x);
}//define the function.

double TR(double c, double h){
    return (h/2)*(f(c-h)+2*f(c)+f(c+h));
}//integrate f(x) from -h to h centered at c using trapezoid rule.

double integrate_by_TR (int N){
    double total=0.0;
    double h=2.0/N;
    for(int i=0; i<N/2; i++){
        total+=TR((2*i+1)*h,h);
    }
    return total;
}//N is the number of latice spacings. loops the TR function to integrate over the whole domain.

double SR(double c, double h){
    return (h/3)*(f(c+h)+4*f(c)+f(c-h));
}//integrate f(x) from -h to h centered at c using Simpson's Rule.

double integrate_by_SR(int N){
    double total=0.0;
    double h=2.0/N;
    for (int i=0;i<N/2; i++){
        total+=SR((2*i+1)*h,h);
    }
    return total;
}//N is the number of latice spacings. loops the TR function to integrate over the whole domain.

double BR(double lb, double h){
    return (2*h/45)*(7*f(lb)+32*f(lb+h)+12*f(lb+2*h)+32*f(lb+3*h)+7*f(lb+4*h));
}//lb is the leftmost bound. integrate from lb to 4h.

double integrate_by_BR(double N){
    double total=0.0;
    double h=2.0/N;
    for (int i=0; i<N/4; i++){
        total+=BR(4*i*h,h);
    }
    return total;
}//N is the number of latice spacings. loops the TR function to integrate over the whole domain.

int main(){
    cout<<setprecision(8)<<"Actual Value = "<<AV<<endl<<endl;
    cout<<"N\tAV - TR\t\tAV - SR\t\tAV - BR"<<endl;
    cout<<setprecision(7)<<scientific;
	cout<<(int)pow(2,1)<<"\t"<<fabs(AV-integrate_by_TR(2))<<"\t"<<fabs(AV-integrate_by_SR(2))<<"\tNot Valid"<<endl;
//	cout<<"4\t"<<fabs(AV-integrate_by_TR(4))<<"\t"<<fabs(AV-integrate_by_SR(4))<<"\t"<<fabs(AV-integrate_by_BR(4))<<endl;
//	cout<<"8\t"<<fabs(AV-integrate_by_TR(8))<<"\t"<<fabs(AV-integrate_by_SR(8))<<"\t"<<fabs(AV-integrate_by_BR(8))<<endl;
//	cout<<"16\t"<<fabs(AV-integrate_by_TR(16))<<"\t"<<fabs(AV-integrate_by_SR(16))<<"\t"<<fabs(AV-integrate_by_BR(16))<<endl;
//	cout<<"32\t"<<fabs(AV-integrate_by_TR(32))<<"\t"<<fabs(AV-integrate_by_SR(32))<<"\t"<<fabs(AV-integrate_by_BR(32))<<endl;
//	cout<<"64\t"<<fabs(AV-integrate_by_TR(64))<<"\t"<<fabs(AV-integrate_by_SR(64))<<"\t"<<fabs(AV-integrate_by_BR(64))<<endl;
//	cout<<"128\t"<<fabs(AV-integrate_by_TR(128))<<"\t"<<fabs(AV-integrate_by_SR(128))<<"\t"<<fabs(AV-integrate_by_BR(128))<<endl;
	for (int i=2; i<=100; i++){
		cout<<(int)pow(2,i)<<"\t"<<fabs(AV-integrate_by_TR(pow(2,i)))<<"\t"<<fabs(AV-integrate_by_SR(pow(2,i)))<<"\t"<<fabs(AV-integrate_by_BR(pow(2,i)))<<endl;
	}
    return 0;
}
