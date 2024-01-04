//Circular Planetary Orbit
#include<iostream>
#include<graphics.h>
#include<cmath>
#include<stdio.h>

using namespace std;

double width=600.0;// window width in pixels
double height=600.0;// window height in pixels
double x_range=4.0; // the range of x in astronomical units (AU)
double y_range=4.0; // the range of y in astronomical units (AU)
double x_scale=width/x_range;// scale of x in pixel per AU
double y_scale=height/y_range;// scale of y in pixel per AU
double revolutions= 50.0; //the number of revolutions, set to 10.0 by default

double dt[]={0.1,0.05, 0.01, 0.005, 0.001, 0.0005, 0.0001};// array of delta_t's
//sprintf to convert to arrays

double x(double _x){
    return (width/2.0)+_x*x_scale;
}//convert from Cartesian to c++ convention

double y(double _y){
    return (height/2.0)-_y*y_scale;
}//convert from Cartesian to c++ convention

class Planet{
private:
    double x=1.0;//x-position of the planet, initially set to 1.0
    double y=0.0;//y-position of the planet, initially set to 0.0
    double v_x=0.0; //x-component of the velocity, initially set yo 0.0
    double v_y=2.0*M_PI;// y-component of the velocity, initially set to 2pi
    double t=0.0;// tells the current time, initially set to 0.0
    double delta_t=0.001;// the time-step in years, default value set to 0.1
    //temporary variables for holding current x and y
    double temp_x=x;
    double temp_y=y;

    double a_x (double _x){
        return -4.0*M_PI*M_PI*_x;
    }// x-component of the acceleration given in AU/year^2
    double a_y (double _y){
        return -4.0*M_PI*M_PI*_y;
    }// y-component of the acceleration given in AU/year

public:
    void update_time(int method){
        if (method==1){
            temp_x=x;
            temp_y=y;
            x+=v_x*delta_t;
            y+=v_y*delta_t;
            v_x+=a_x(temp_x)*delta_t;
            v_y+=a_y(temp_y)*delta_t;
        }
        else if (method==2){
            v_x+=a_x(x)*delta_t;
            v_y+=a_y(y)*delta_t;
            x+=v_x*delta_t;
            y+=v_y*delta_t;
        }
            t+=delta_t;
    }// allow time to move by one time step. The argument takes in 1 for Euler and 2 for Euler-Cromer.

    //these return the current x and y positions of the planet
    double current_x(){
        return x;
    }
    double current_y(){
        return y;
    }
    void reset(){
        x=1.0;
        y=0.0;
        v_x=0.0;
        v_y=2.0*M_PI;
        t=0.0;
    }
    void set_delta_t(double dT){
        delta_t=dT;
    }
};

void graph_grid(){
    for (int i=1; i<=3; i++) line(x_scale*i,0,x_scale*i,height);
    for (int i=1; i<=3; i++) line(0,y_scale*i,width,y_scale*i);
    settextjustify(LEFT_TEXT, BOTTOM_TEXT);
    settextstyle(10, HORIZ_DIR, 3);
    outtextxy(x(-x_range/4.0*1.25),y(-y_range/4*1.25),"Press any key to continue");
    setcolor(YELLOW);
    circle(x(0),y(0),width/40.0);
    setfillstyle(SOLID_FILL,YELLOW);
    floodfill(x(0),y(0),YELLOW);
    setcolor(WHITE);
}

int main(){
    char buffer[50];
    Planet earth; //instantiate a Planet object, call it earth
    initwindow(width,height);
    for (int method=1; method<=2; method++){
        for (int i=0; i<7; i++){
            earth.set_delta_t(dt[i]);
            graph_grid();

            //window text stuff
            if (method==1) outtextxy(x(-x_range/4.0*1.75),y(y_range/4*1.5),"EULER METHOD");
            else if (method==2) outtextxy(x(-x_range/4.0*1.75),y(y_range/4*1.5),"EULER-CROMER METHOD");
            sprintf(buffer,"deltaT = %.6f",dt[i]);
            outtextxy(x(-x_range/4.0*1.75),y(y_range/4*1.25),buffer);

            //graph the orbit
            moveto(x(earth.current_x()),y(earth.current_y()));
            for (int j=0; j<revolutions/dt[i]; j++){
                    lineto(x(earth.current_x()),y(earth.current_y()));
                    earth.update_time(method);
            }

            getch();
            cleardevice();
            earth.reset();//reset to initial conditions
        }
    }
    return 0;
}
