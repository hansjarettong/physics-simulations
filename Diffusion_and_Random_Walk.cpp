//diffusion and random walk in 1D
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

//discretization parameters
double delta_x=1.0;
double delta_t=0.5;
double D=1.0;

double x_range=100.0; //assume that the graph is always centered at x=0
double y_max=1.0; //where is minimum value of y is 0

char buffer[50];

int array_size=round(x_range/delta_x);

//density array
double *rho=new double[array_size];

//x-coordinate to array index
int index_at(double x){
    return (x+x_range/2.0)/delta_x;
}


//for scaling. converts cartesean to pixels
double x(double _x){
    return _x*width/2.0*1.5/x_range+width/2.0;
}

double y(double _y){
    return (_y-y_max)*(-0.75*height)/y_max+height/8.0;
}

void reset_rho(){
    for (int i=0; i<array_size; i++){
        if(i==index_at(0)) rho[i]=1;
        else rho[i]=0;
    }
}


void update_rho_time(){
    double *temp_rho=new double[array_size];// to be added to the original rho
    for (int i=0; i<array_size; i++){
        temp_rho[i]=0;
    }
    for (int i=1; i<array_size-1; i++){
        temp_rho[i]=D*delta_t/(delta_x*delta_x)*(rho[i+1]+rho[i-1]-2*rho[i]);
    }
    for (int i=0; i<array_size; i++){
        rho[i]+=temp_rho[i];
    }
    delete [] temp_rho;
}

double rho_max(){
    double current_max=0.0;
    for (int i=0; i<array_size; i++){
        if(rho[i]>current_max) current_max=rho[i];
    }
    return current_max;
}

void graph_rho(){
    moveto(x(-x_range/2.0),y(0.0));
    for (int i=0; i<array_size; i++){
        lineto(x(i*delta_x-x_range/2.0),y(rho[i]));
    }
}

//RANDOM-WALK STUFF
const int no_of_walkers=5000;
double walkers[no_of_walkers]={0};

void reset_walkers(){
    for (int i=0; i<no_of_walkers; i++){
        walkers[i]=0;
    }
}

double random_step(){
    double temp= double(rand())/RAND_MAX;
    if(temp<0.5) return -delta_x;
    else return delta_x;
}

void update_walker_time(){
    for (int i=0; i<no_of_walkers; i++){
        walkers[i]+=random_step();
    }
}

//gets the histogram of the walkers' positions
void walker_to_rho(){
    double *temp_rho=new double[array_size];// to be added to the original rho
    for (int i=0; i<array_size; i++){
        temp_rho[i]=0;
    }
    for (int i=0; i<no_of_walkers; i++){
        temp_rho[index_at(walkers[i])]+=1;
    }
    for (int i=0; i<array_size; i++){
        rho[i]=temp_rho[i]/no_of_walkers;
    }
    delete [] temp_rho;
}

void graph_axes(){
    sprintf(buffer, "%.6f", y_max);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(3, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(x(0),height*7.25/8,"x=0");
    outtextxy(x(0),y(0),"|");
    outtextxy(5.5*width/7,7.3*width/8,"Press any key to continue");
    outtextxy(width/20, y(y_max), buffer);
    line(x(-x_range/2.0),0,x(-x_range/2.0),height);
    line(0,y(0.0),width,y(0.0));
    line(x(-x_range/2.0),y(y_max),x(x_range/2.0),y(y_max));
    line(x(x_range/2.0),y(y_max),x(x_range/2.0),y(0.0));
}

int main(){
    srand(time(0));
    reset_rho();
    initwindow(width, height);
    graph_axes();
    //for diffusion
    reset_rho();
    for (int t=0; t<=100; t++){
        if(t==0|| t==10|| t==100){
            y_max=rho_max();
            cleardevice();
            graph_axes();
            outtextxy(0.75*width, 0.25*height,"Diffusion");
            graph_rho();
            getch();
        }
        update_rho_time();
    }

    //for random_walk
    for (int t=0; t<=100; t++){
        if(t==0||t==10||t==100){
            walker_to_rho();
            y_max=rho_max();
            cleardevice();
            graph_axes();
            outtextxy(0.75*width, 0.25*height, "Random Walk");
            graph_rho();
            getch();
        }
        update_walker_time();
    }

    getch();
    return 0;
}
