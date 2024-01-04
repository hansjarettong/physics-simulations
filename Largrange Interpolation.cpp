//Lagrange interpolation
#include<iostream>
#include<graphics.h>
#include<cmath>

using namespace std;

double width=800.0;// window width in pixels
double height=600.0;// window height in pixels
double x_range=8.0*M_PI; // the range of x in units
double y_range=20.0; // the range of y in units
double x_scale=width/x_range;// scale of x in pixel per unit
double y_scale=height/y_range;// scale of y in pixel per unit
int n=1;// the degree of the polynomial. Set to 1 by default


double f(double x){
    return 1.2+5.0*sin((4+x)*(4+x)/20.0);
}// the function f

double x(double _x){
    return (width/2.0)+_x*x_scale;
}//convert from Cartesian to c++ convention

double y(double _y){
    return (height/2.0)-_y*y_scale;
}//convert from Cartesian to c++ convention

double l_k(double x,int k){
    double temp=1.0;
    for (int i=0; i<=n; i++){
        if (i!=k) temp*=(x-(-x_range/2.0+i*x_range/n));
    }
    return temp;
}//the function l_k

double p_n(double x){
    double temp=0.0;
    for(int i=0; i<=n; i++){
        temp+=l_k(x,i)/l_k((-x_range/2.0+i*x_range/n),i)*f(-x_range/2.0+i*x_range/n);
    }
    return temp;
}//the polynomial p_n

void graph_axes(){
    line(0,height/2,width, height/2);
    line(width/2,0, width/2, height);
    setcolor(WHITE);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(2, HORIZ_DIR, 5);
    outtextxy(x(-3*M_PI),y(-y_range/20),"-3PI");
    outtextxy(x(-2*M_PI),y(-y_range/20),"-2PI");
    outtextxy(x(-M_PI),y(-y_range/20),"-PI");
    outtextxy(x(0),y(-y_range/20),"0.0");
    outtextxy(x(M_PI),y(-y_range/20),"PI");
    outtextxy(x(2*M_PI),y(-y_range/20),"2PI");
    outtextxy(x(3*M_PI),y(-y_range/20),"3PI");
}//graph the x and y axes with the x-axis labels

void graph_f(){
    moveto(0,y(f((-width/2.0)*x_range/width)));
    for(int i=1; i<width; i++){
        lineto(i,y(f((i-width/2.0)*x_range/width)));
    }
}//graph the function f

void graph_pn(){
    setcolor(YELLOW);
    moveto(0,y(p_n((-width/2.0)*x_range/width)));
    for(int i=1; i<width; i++){
        lineto(i,y(p_n((i-width/2.0)*x_range/width)));
    }
}//graph the polynomial p_n


int main(){
    while(1){
        cout<<"Enter the degree n of the polynomial:";
        cin>>n;
        if (n<1) {
            cout<<"n must be greater than or equal to 1!"<<endl;
            continue;
        }
        initwindow(width, height);
        graph_axes();
        graph_f();
        graph_pn();
        getch();
        closegraph();
    }
    return 0;
}
