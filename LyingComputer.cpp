//the computer may lie
#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

double truncate=pow(10,14);

double D(double x){
	if(x>=0.0 && x<0.5) return 2.0*x;
	else return 2.0*x-1.0;
}

class seed{
    double x_n=0.0;
	public:
		void set_x0 (double x){
			x_n=x;
		}
		void iterate (){
			x_n=D(x_n);
			x_n=round(x_n*truncate)/truncate;
		}
		double get_xn(){
			return x_n;
		}
};

int main(){
	cout<<fixed;
	cout<<"Orbits of the Doubling Function"<<endl<<endl;

// create the table for x0=1/5
	seed one_fifth;
	one_fifth.set_x0(1.0/5.0);
	cout<<"seed x0=1/5"<<endl<<setw(10);
	for (int i=0; i<=327; i++){
		if (i<=11 || (i>=316 && i<=327)){
			cout<<one_fifth.get_xn()<<setw(10);
			if (i%4==3) cout<<endl;
		}
		else if (i==12) cout<<endl;
		one_fifth.iterate();
	}

// create the table for x0=1/9
	seed one_ninth;
	one_ninth.set_x0(1.0/9.0);
	cout<<endl<<endl<<"seed x0=1/9"<<endl<<setw(10);
	for (int i=0; i<=491; i++){
		if (i<=17 || (i>=474 && i<=491)){
			cout<<one_ninth.get_xn()<<setw(10);
			if (i%6==5) cout<<endl;
		}
		else if (i==18) cout<<endl;
		one_ninth.iterate();
	}

	return 0;
}
