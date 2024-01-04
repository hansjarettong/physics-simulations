//Random walk in one dimension
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <graphics.h>
#include <stdio.h>

using namespace std;

double position[500]={0};//stores the position of the 500 walkers
const int number_of_steps=100;
double mean_squares[number_of_steps];//stores the mean square per step

double width=800;
double height=800;


//converts cartesean to pixel convention
double x(double _x){
    return (_x+20)*width/140.0;
}

double y(double _y){
    return height*(115-_y)/130.0;
}

void graph_axes(){
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(3, HORIZ_DIR, 1);
    for(int i=0; i<=10; i++){
        outtextxy(x(10*i),y(0),"|");
        outtextxy(x(0), y(10*i), "__");
    }
    line(0,y(0),width,y(0));
    line(x(0),0,x(0),height);
    line(x(0),y(100),x(100),y(100));
    line(x(100),y(100),x(100),y(0));

    settextstyle(3,HORIZ_DIR,2);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(width/2,12.0*height/13, "Step Number");
    outtextxy(width/14,12.0*height/13,"0");
    outtextxy(x(100),12.0*height/13,"100");
    outtextxy(width/14,y(100),"100");
    outtextxy(width/14,y(50),"<Xm2>");
}

double random_step(){
    return -1.0+double(rand())/RAND_MAX*2.0;
}//returns values from -1 to 1

double mean_square(double x[500]){
    double temp=0;
    for(int i=0; i<500; i++){
        temp+=x[i]*x[i];
    }
    return temp/500.0;
}//gets the mean square of the position of the 500 walkers

double least_squares_slope(double _array[number_of_steps]){
    double sum_xy=0.0;
    double sum_x=0.0;
    double sum_y=0.0;
    double sum_x2=0.0;
    for (int i=0; i<number_of_steps; i++){
        sum_xy+=i *_array[i];
        sum_x+=i;
        sum_y+=_array[i];
        sum_x2+=i*i;
    }
    return (number_of_steps*sum_xy-sum_x*sum_y)/(number_of_steps*sum_x2-sum_x*sum_x);
}// get the least squares slope of the points

int main (){
    srand(time(0));
    char buffer[50];
    initwindow(width,height);
    graph_axes();
    setcolor(CYAN);
    for(int step=0; step<number_of_steps; step++){
        circle(x(step),y(mean_square(position)),width/300);
        mean_squares[step]=mean_square(position);
        for (int i=0; i<500; i++){
            position[i]+=random_step();
        }//makes the walkers take one random step
    }
    sprintf(buffer,"The slope is D = %.6f", least_squares_slope(mean_squares));
    setcolor(WHITE);
    outtextxy(width/2, height/2, buffer);
    line(x(0),y(0),x(100),y(100*least_squares_slope(mean_squares)));
    getch();
    return 0;
}
