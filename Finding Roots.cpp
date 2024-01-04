//finding roots
#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

double tolerance=pow(10,-6);
double x_r=sqrt(5.0);

double f(double x){
	return x*x-5;
}//define f(x)

double f_p(double x){
	return 2*x;
}//define f'(x)

class Search{
	double x_n=1.0;
	double h=0.5;
	public:	
		void iterate(){
			if (x_n<x_r) x_n+=h;
			else{
				x_n-=h;
				h/=2.0;
				x_n+=h;
			}
		}
		double get_x_n(){
			return x_n;
		}
};

class Newton{
	double x_n=1.0;
	public:
		double N(double x){
			return x-f(x)/f_p(x);
		}
		void iterate(){
			x_n=N(x_n);
		}
		double get_x_n(){
			return x_n;
		}
};

class Secant{
	double x_n=1.0;
	double x_n_less_1=0.5;
	double temp=0.0;
	public:
		double N(double x_0, double x_1){
			if (f(x_1)-f(x_0)==0) return x_n; //this is to prevent nan error
			return x_1-f(x_1)*(x_1-x_0)/(f(x_1)-f(x_0));
		}
		void iterate(){
			temp=x_n;
			x_n=N(x_n_less_1,x_n);
			x_n_less_1=temp;
		}
		double get_x_n(){
			return x_n;
		}
};

int main(){
	cout<<fixed<<right;
	//declare instances of my classes
	Search _search;
	Newton newton;
	Secant secant;
	cout<<"iteration    Search         Newton         Secant"<<endl<<endl;
	int i=0;//this is the number of iterations
	while ((fabs(5-_search.get_x_n()*_search.get_x_n())>tolerance) || (fabs(5-newton.get_x_n()*newton.get_x_n())>tolerance) || (fabs(5-secant.get_x_n()*secant.get_x_n())>tolerance)){
		cout<<setw(5)<<i<<setw(15)<<x_r-_search.get_x_n()<<setw(15)<<x_r-newton.get_x_n()<<setw(15)<<x_r-secant.get_x_n()<<endl;
		_search.iterate();
		newton.iterate();
		secant.iterate();
		i++;
	}
	return 0;
}
