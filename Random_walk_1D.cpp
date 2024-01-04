//Random walk in one dimension
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <graphics.h>

using namespace std;

int position[500]={0};//stores the position of the 500 walkers
int number_of_steps=100;

double width=800;
double height=800;


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
    line(x(0),y(0),x(100),y(100));
    settextstyle(3,HORIZ_DIR,2);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(width/2,12.0*height/13, "Step Number");
    outtextxy(width/14,12.0*height/13,"0");
    outtextxy(x(100),12.0*height/13,"100");
    outtextxy(width/14,y(100),"100");
    outtextxy(width/14,y(50),"<Xm2>");
}

int random_step(){
    double temp=double(rand())/RAND_MAX*2.0;
    if (temp<=1) return -1;
    else return 1;
}//returns +1 or -1

double mean_square(int x[500]){
    double temp=0;
    for(int i=0; i<500; i++){
        temp+=x[i]*x[i];
    }
    return temp/500.0;
}

int main (){
    srand(time(0));
    initwindow(width,height);
    graph_axes();
    setcolor(CYAN);
    for(int step=0; step<number_of_steps; step++){
        circle(x(step),y(mean_square(position)),width/300);
        for (int i=0; i<500; i++){
            position[i]+=random_step();
        }//makes the walkers take one random step
    }
    getch();
    return 0;
}
