//Monte Carlo Integration
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <iomanip>

using namespace std;

int Ntotal=0;
double x,y;

int darts_in_circle_counter(int ntotal){
    int counter=0;
    for (int i=0; i<ntotal; i++){
        x=-1.0+double(rand())/RAND_MAX*2.0;
        y=-1.0+double(rand())/RAND_MAX*2.0;
        if(x*x+y*y<=1.0) counter++;
    }
    return counter;

}

int main(){
    srand(time(0));
    cout<<"Ntotal\t\tArea of Circle"<<endl;
    for (int i=9; i<=9;i++){
        Ntotal=round(pow(10,i));
        cout<<right<<setw(10)<<Ntotal<<setprecision(7)<<"\t"<<darts_in_circle_counter(Ntotal)/double(Ntotal)*4.0<<endl;
    }
    return 0;
}
