//Multistep methods version 3
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<graphics.h>

using namespace std;

double width=1200.0;// window width in pixels
double height=700.0;// window height in pixels

double h=0.01;

double x(double _x){
    return width*(_x+0.7)/2.9;
}//convert from Cartesian to c++ convention. Assuming that the display range is -0.7<t<2.2.

double y(double _y){
    return (_y+0.75)*(-height/5.3)+height;
}//convert from Cartesian to c++ convention. Assuming that the display range is 0.75<y<5.3.

double f(double t, double y){
    return -5.0*y+5.0*t*t+2*t;
}

double actual_y(double t){
    return t*t+(1.0/3)*exp(-5.0*t);
}

double runge_kutta(int n){
    double yn=actual_y(-0.5);
    double k1,k2,k3,k4;
    for(int i=0; i<n; i++){
        k1=h*f(-0.5+i*h,yn);
        k2=h*f(-0.5+i*h+0.5*h, yn+0.5*k1);
        k3=h*f(-0.5+i*h+0.5*h, yn+0.5*k2);
        k4=h*f(-0.5+i*h+h, yn+k3);
        yn+=1.0/6*(k1+2.0*k2+2.0*k3+k4);
    }
    return yn;
}//look for the y_n. where y_0=actual_y(-0.5)


void graph_axes(){
    char buffer[50];
    line(0,y(0),width,y(0));
    line(x(0),0, x(0),height);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    settextstyle(3, HORIZ_DIR, 2);
    for (int i=-1; i<=6; i++){
        sprintf(buffer, "%.1f", i/2.0);
        outtextxy(x(i/2.0), y(-0.1),buffer);
    }
}

void graph_actual(){
    moveto(x(-0.5),y(actual_y(2.9/width*x(-0.5)-0.7)));
    for (int i=x(-0.5); i<=x(2.0); i++){
        lineto(i,y(actual_y(2.9/width*i-0.7)));
    }
    settextjustify(CENTER_TEXT,TOP_TEXT);
    outtextxy(2*width/3, height/3,"Actual Solution");
}

class Multistep{
private:
    double y0=actual_y(-0.5);
    double y1=runge_kutta(1);
    double y2=runge_kutta(2);
    double y3=runge_kutta(3);
    double y4=runge_kutta(4);
    double temp=0.0;
    double t=-0.5;


    int method=2;
    /*values of int method:
    2: two step explicit
    3:three step explicit
    6:three step implicit
    4: four step explicit
    7:four step implicit
    5: five step explicit
    */

    void two_step_iterate(){
        temp=h/2.0*(3.0*f(t,y1)-f(t-h,y0));
        y0=y1;
        y1+=temp;
        t+=h;
    }

    void three_step_explicit(){
        temp=h/12.0*(23.0*f(t,y2)-16.0*f(t-h,y1)+5.0*f(t-2*h,y0));
        y0=y1;
        y1=y2;
        y2+=temp;
        t+=h;
    }

    void three_step_implicit(){
        temp=h/24.0*(9.0*f(t+h,y3)+19.0*f(t,y2)-5.0*f(t-h,y1)+f(t-h,y0));
        y0=y1;
        y1=y2;
        y2+=temp;
        y3=y2;
        t+=h;
    }

    void four_step_explicit(){
        temp=h/24.0*(55.0*f(t,y3)-59.0*f(t-h,y2)+37.0*f(t-2*h,y1)-9.0*f(t-3*h,y0));
        y0=y1;
        y1=y2;
        y2=y3;
        y3+=temp;
        t+=h;
    }

    void four_step_implicit(){
        temp=h/720.0*(251.0*f(t+h,y4)+646.0*f(t,y3)-264.0*f(t-h,y2)+106.0*f(t-2*h,y1)-19.0*f(t-3*h,y0));
        y0=y1;
        y1=y2;
        y2=y3;
        y3+=temp;
        y4=y3;
        t+=h;
    }

    void five_step(){
        temp=h/720.0*(1901.0*f(t,y4)-2774.0*f(t-h,y3)+2616.0*f(t-2*h,y2)-1274.0*f(t-3*h,y1)+251.0*f(t-4*h,y0));
        y0=y1;
        y1=y2;
        y2=y3;
        y3=y4;
        y4+=temp;
        t+=h;
    }


public:
    void init(int _method){
        method=_method;
        y0=actual_y(-0.5);
        y1=runge_kutta(1);
        y2=runge_kutta(2);
        y3=runge_kutta(3);
        y4=runge_kutta(4);
        temp=0.0;
        t=-0.5;
        switch(_method){
            case 2: t+=h; break;
            case 3: t+=2*h; break;
            case 6:t+=2*h; break;
            case 4: t+=3*h; break;
            case 7:t+=3*h; break;
            case 5: t+=4*h; break;
        }

    }


    void graph(){
        if(method==2){
            moveto(x(-0.5),y(y0));
            while (t<=2.0){
                lineto(x(t),y(y1));
                two_step_iterate();
            }
            settextjustify(CENTER_TEXT,TOP_TEXT);
            outtextxy(2*width/3, height/3,"Adams-Bashforth Two-Step Explicit Method");
        }

        else if(method==3){
            moveto(x(-0.5),y(y0));
            lineto(x(-0.5+h),y(y1));
            while (t<=2.0){
                lineto(x(t),y(y2));
                three_step_explicit();
            }
            settextjustify(CENTER_TEXT,TOP_TEXT);
            outtextxy(2*width/3, height/3,"Adams-Bashforth Three-Step Explicit Method");
        }

        else if(method==6){
            moveto(x(-0.5),y(y0));
            lineto(x(-0.5+h),y(y1));
            while (t<=2.0){
                lineto(x(t),y(y2));
                three_step_implicit();
            }
            settextjustify(CENTER_TEXT,TOP_TEXT);
            outtextxy(2*width/3, height/3,"Adams-Bashforth Three-Step Implicit Method");
        }
        else if(method==4){
            moveto(x(-0.5),y(y0));
            lineto(x(-0.5+h),y(y1));
            lineto(x(-0.5+2*h),y(y2));
            while (t<=2.0){
                lineto(x(t),y(y3));
                four_step_explicit();
            }
            settextjustify(CENTER_TEXT,TOP_TEXT);
            outtextxy(2*width/3, height/3,"Adams-Bashforth Four-Step Explicit Method");
        }
        else if(method==7){
            moveto(x(-0.5),y(y0));
            lineto(x(-0.5+h),y(y1));
            lineto(x(-0.5+2*h),y(y2));
            while (t<=2.0){
                lineto(x(t),y(y3));
                four_step_implicit();
            }
            settextjustify(CENTER_TEXT,TOP_TEXT);
            outtextxy(2*width/3, height/3,"Adams-Bashforth Four-Step Implicit Method");
        }
        else if(method==5){
            moveto(x(-0.5),y(y0));
            lineto(x(-0.5+h),y(y1));
            lineto(x(-0.5+2*h),y(y2));
            lineto(x(-0.5+3*h),y(y3));
            while (t<=2.0){
                lineto(x(t),y(y4));
                five_step();
            }
            settextjustify(CENTER_TEXT,TOP_TEXT);
            outtextxy(2*width/3, height/3,"Adams-Bashforth Five-Step Explicit Method");
        }
    }

};


int main(){
    Multistep object;
    initwindow(width,height);
    graph_axes();
    setcolor(CYAN);
    graph_actual();
    setcolor(WHITE);
    getch();
    cleardevice();
    for (int i=2; i<=7; i++){
        graph_axes();
        setcolor(CYAN);
        graph_actual();
        setcolor(YELLOW);
        object.init(i);
        object.graph();
        setcolor(WHITE);
        getch();
        cleardevice();
    }
    return 0;
}
