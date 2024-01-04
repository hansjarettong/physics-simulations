//Heat: Time Evolution
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <graphics.h>
#include <stdio.h>

using namespace std;

//window dimensions in pixels
double width=800;
double height=800;

char buffer[50];

int x_min=0;
int x_max=100;
int y_min=0;
int y_max=100;

double temperature[101][101]={0};

double f=1.0/10000;
double c=1.0;
double delta_h=1.0;
double delta_t=0.125;

double r=delta_t*c*c/delta_h/delta_h;

double x(double _x){
    return (_x-x_min)*(4*width/5.0)/double(x_max-x_min)+3.0*width/20;
}

double y(double _y){
    return (_y-y_max)*(-17.0*height/20)/double(y_max-y_min)+height/20.0;
}

void graph_axes(){
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(3, HORIZ_DIR, 2);
    setcolor(WHITE);
    for(int i=1; i<20; i++){
        outtextxy(x(x_min+((x_max-x_min)/20)*i),y(y_min),"|");
        outtextxy(x(x_min), y(y_min+((y_max-y_min)/20)*i), "__");
    }

    outtextxy(0.75*width,height/30.0,"Press any key to continue");

    sprintf(buffer, "%.1f", double(y_max));
    outtextxy(2*width/20.0,height/20.0,buffer);
    sprintf(buffer, "%.1f", double(y_max+y_min)/2.0);
    outtextxy(2*width/20.0,height/2.0,buffer);
    sprintf(buffer, "%.1f", double(y_min));

    outtextxy(2*width/20.0,9.0*height/10.0,buffer);
    line(x(x_min),y(y_max),x(x_max),y(y_max));
    line(x(x_max),y(y_max),x(x_max),y(y_min));
    line(x(x_max),y(y_min),x(x_min),y(y_min));
    line(x(x_min),y(y_min),x(x_min),y(y_max));
    line(x(0),y(y_max),x(0),y(y_min));
    line(x(x_min),y(0),x(x_max),y(0));

}

void graph_temperature(){
    for(int i=0; i<100; i++){
        for (int j=0; j<100; j++){
            setfillstyle(1, 15-int(temperature[i][j]*16.0/101));
            bar(x(i),y(j+1),x(i+1),y(j));
            //cout<<x(i)<<endl;
        }
    }
}

void update_temperature_steady_state(){
    for (int i=1; i<100; i++){
        for (int j=1; j<100; j++){
            temperature[i][j]=0.25*(temperature[i+1][j]+temperature[i][j+1]+temperature[i-1][j]+temperature[i][j-1]);
        }
    }
}

double left_boundary(int j, int t){
    return 50+50*sin(2*M_PI*(j/100.0+f*t));
}

void update_temperature_changing_BC(){
    for(int i=1; i<100; i++){
        for(int j=1; j<100; j++){
            temperature[i][j]=(1-4*r)*temperature[i][j]+r*(temperature[i+1][j]+temperature[i-1][j]+temperature[i][j+1]+temperature[i][j-1]);
        }
    }
}


int main(){
    //initialize temerature array
    for(int i=0; i<101; i++){
        for (int j=0; j<101; j++){
            if(j==0) temperature[i][j]=i;
            else if(j==100) temperature[i][j]=100-i;
            else if(i==100) temperature[i][j]=100;
            else if (i==0) temperature[i][j]=left_boundary(j,0);
            else temperature[i][j]=50;
        }
    }

    initwindow(width,height);
    graph_axes();
    graph_temperature();

    //we let it reach steady state first
    for(int t=1; t<=10000; t++){
        if(t==10000) {
            graph_temperature();
            getch();
        }
        update_temperature_steady_state();
    }

    //now we let the left boundary change
    for (int t=1; t<=12000; t++){
        //update the left BC
        for(int j=0; j<101;j++) temperature[0][j]=left_boundary(j,t);
        if(t%2000==0){
            sprintf(buffer, "time step=%d", t);
            outtextxy(width/2.0,height/20.0,buffer);
            graph_temperature();
            getch();
        }
        update_temperature_changing_BC();
    }

    getch();
    return 0;
}
