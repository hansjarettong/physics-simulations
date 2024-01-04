//Chaos in Newton's method
#include<iostream>
#include<cmath>
#include<graphics.h>

using namespace std;

double width=600.0;//window width in pixels
double height=600.0;//windows height in pixels
double x_range=8.0; // the range of x in units
double y_range=8.0; // the range of y in units
double x_scale=width/x_range;// scale of x in pixel per unit
double y_scale=height/y_range;// scale of y in pixel per unit

double x_0=1.20;//seed

double F(double x){
    return x*x+1;
}//the function F

double F_p(double x){
    return 2*x;
}// F prime or F derivative

double N(double x){
    return x-F(x)/F_p(x);
}//the iteration function N

double x(double _x){
    return (width/2.0)+_x*x_scale;
}//convert from Cartesian to c++ convention

double y(double _y){
    return (height/2.0)-_y*y_scale;
}//convert from Cartesian to c++ convention

void graph_axes(){
    line(0,height/2,width, height/2);
    line(width/2,0, width/2, height);
}//graph the x and y axes

void graph_N(){
    moveto(0,y(N((-width/2.0)*x_range/width)));
    for(int i=1; i<width; i++){
        lineto(i,y(N((i-width/2.0)*x_range/width)));
    }
}//graph N

void graph_y_x(){
    moveto(0,y((-width/2.0)*x_range/width));
    for(int i=1; i<width; i++){
        lineto(i,y((i-width/2.0)*x_range/width));
    }
}// graph of y=x


int main(){

    initwindow(width, height);
    graph_axes();
    graph_N();
    graph_y_x();

    line(x(x_0),y(0),x(x_0),y(N(x_0)));
    for (int i=0; i<500; i++){
        setcolor(YELLOW);
        line(x(x_0),y(N(x_0)),x(N(x_0)),y(N(x_0)));
        x_0=N(x_0);
        line(x(x_0),y(x_0),x(x_0),y(N(x_0)));
    }
    getch();
    closegraph();
    return 0;
}
