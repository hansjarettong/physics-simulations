//Gaussian Random Numbers
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <graphics.h>

using namespace std;

//window dimensions in pixels
double width=800;
double height=800;


double y_c=1.0;// the mean of the Gaussian distribution
double sigma=1.0;// standard deviation of the Gaussian distribution
double P_ymax=1.0;// the maximum value which would be used for B- the normalization factor for P_y


double bin_size[4]={0.32, 0.32/2, 0.32/3, 0.32/4};// bin sizes for the 4 cases
int n_random[4]={100,1000,10000,100000}; // number of random numbers for the 4 cases

double x(double _x){
    return (_x+4)*width/8.0;
}

double y(double _y){
    return -height*(_y-1.25)/1.5;
}

double P_y(double y,double B){
    return B*exp(-(y-y_c)*(y-y_c)/sigma/sigma);
}

double y_i(){
    return -4.0+double(rand())*8.0/RAND_MAX;
}

double P_test(){
    return double(rand())*P_ymax/RAND_MAX;
}

void graph_case_i(int i){
    double yi=0.0;
    double p_yi=0.0;
    int max_count=0;
    int b_n=0;
    int number_of_bins=8.0/bin_size[i];
    int bin_counter[number_of_bins]={0};
    for (int j=0; j<n_random[i]; j++){
        yi=y_i();
        p_yi=P_y(yi,P_ymax);
        if(p_yi>P_test()){
            b_n=floor((yi+4)/bin_size[i]);
            bin_counter[b_n]++;
        }
    }
    for(int k=0; k<number_of_bins; k++){
        if(bin_counter[k]>max_count) max_count=bin_counter[k];
    }
    moveto(x(-4.0),y(double(bin_counter[0])/max_count));
    for(int k=0; k<number_of_bins; k++){
        lineto(x(-4.0+bin_size[i]*(k+0.5)),y(double(bin_counter[k])/max_count));
    }

}

void graph_axes(){
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(3, HORIZ_DIR, 2);
    for (int i=-2; i<=3; i++){
        outtextxy(x(i), y(0.0),"|");
    }
    outtextxy(x(-3.0),y(-0.05),"x=-3.0");
    outtextxy(x(1.0),y(-0.05),"x=1.0");
    outtextxy(x(-3.5),y(1.0),"y=1.0");
    outtextxy(x(-3.0),y(1.0),"--");
    line(x(-3.0),0,x(-3.0),height);
    line(0,y(0.0),width,y(0.0));
}

void graph_actual(){
    for (int i=x(-4.0); i<=x(4.0); i++){
        lineto(i,y(P_y(8.0/width*i-4.0,P_ymax)));
    }
}

int main(){
    srand(time(0));
    initwindow(width, height);
    graph_axes();
    graph_actual();
    setcolor(CYAN);
    graph_case_i(0);
    setcolor(RED);
    graph_case_i(1);
    setcolor(YELLOW);
    graph_case_i(2);
    setcolor(GREEN);
    graph_case_i(3);
    getch();
    return 0;
}
