//cubic spline interpolation
#include<iostream>
#include<graphics.h>
#include<cmath>

using namespace std;

double width=800.0;// window width in pixels
double height=600.0;// window height in pixels
double x_range=0.01*M_PI; // the range of x in units
double y_range=20.0; // the range of y in units
double x_scale=width/x_range;// scale of x in pixel per unit
double y_scale=height/y_range;// scale of y in pixel per unit
int n=1;// the degree of the polynomial. Set to 1 by default


double f(double x){
    //return 1.2+5.0*sin((4+x)*(4+x)/20.0);
    return sin(1.0/x);
}// the function f

double x(double _x){
    return (width/2.0)+_x*x_scale;
}//convert from Cartesian to c++ convention

double y(double _y){
    return (height/2.0)-_y*y_scale;
}//convert from Cartesian to c++ convention


double x_i(int i){
    return -x_range/2.0+i*x_range/n;
}//x_i

double h(int i){
    return x_i(i+1)-x_i(i);
}//h_i

double a(int i){
    return f(x_i(i));
}//a_j

double alpha(int i){
    return (3.0/h(i))*(a(i+1)-a(i))-(3.0/h(i-1))*(a(i)-a(i-1));
}//alpha_i

double l(int i){
    if (i==0 || i==n) return 1.0;
    else if (i==1) return 2.0*(x_i(i+1)-x_i(i-1));// because u_0=0, thus h(0)/l(0)=0.
    return 2.0*(x_i(i+1)-x_i(i-1))-h(i-1)*h(i-1)/l(i-1);// I changed u(i-1) to h(i-1)/l(i-1)
}//l_i

double u(int i){
    if (i==0) return 0.0;
    return h(i)/l(i);
}//u_i

double z(int i){
    if (i==0 || i==n) return 0.0;
    return (alpha(i)-h(i-1)*z(i-1))/l(i);
}//z_i

double c(int j){
    if (j==n) return 0.0;
    return z(j)-u(j)*c(j+1);
}//c_j

double b(int j){
    return (a(j+1)-a(j))/h(j)-h(j)*(c(j+1)+2.0*c(j))/3.0;
}//b_j

double d(int j){
    return (c(j+1)-c(j))/(3.0*h(j));
}//d_j

double S(double x, int j){
    return a(j)+b(j)*(x-x_i(j))+c(j)*(x-x_i(j))*(x-x_i(j))+d(j)*(x-x_i(j))*(x-x_i(j))*(x-x_i(j));
}//The jth cubic polynomial S_j(x)

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

void graph_S(){
    setcolor(YELLOW);
    int j=0;
    moveto(0,y(S((-width/2.0)*x_range/width,j)));
    for (int i=0; i<width; i++){
        if (i>width*x_i(j)/x_range+width/2.0 && i<width*x_i(j+1)/x_range+width/2.0){
            lineto(i,y(S((i-width/2.0)*x_range/width,j)));
        }
        else if (i>width*x_i(j+1)/x_range+width/2.0 && i<width*x_i(j+2)/x_range+width/2.0){
            j++;
        }
    }
}//graph the interpolated function S(x)


int main(){
    while(true){
        cout<<"Enter n:";
        cin>>n;
        if (n<1) {
            cout<<"n must be greater than or equal to 1!"<<endl;
            continue;
        }
        initwindow(width, height);
        graph_axes();
        graph_f();
        graph_S();
        getch();
        closegraph();
    }
    return 0;
}
