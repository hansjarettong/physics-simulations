//Minor Project 2
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

int x_min=-100;
int x_max=100;
int y_min=-100;
int y_max=100;

char buffer[50];

int step_size=1;
int number_of_molecules=400;

class Molecule{
private:
    int x_pos=0;
    int y_pos=0;
public:
    int x(){
        return x_pos;
    }
    int y(){
        return y_pos;
    }
    void walk(){
        double temp=double(rand())/RAND_MAX;
        //take random step
        if(temp<=0.25) x_pos+=step_size;
        else if(temp>0.25 && temp<=0.5) x_pos-=step_size;
        else if(temp>0.5 && temp<=0.75) y_pos+=step_size;
        else y_pos-=step_size;
        //to make sure the molecules stays in the container
        if (x_pos>x_max) x_pos-=2*step_size;
        else if(x_pos<=x_min) x_pos+=2*step_size;
        else if(y_pos>y_max) y_pos-=2*step_size;
        else if (y_pos<=y_min) y_pos+=2*step_size;
    }
};

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


int main(){
    srand(time(0));
    initwindow(width, height);
    graph_axes();
    //trajectory of a single molecule
    Molecule single_molecule;
    for (int t=0; t<40000; t++){
        putpixel(x(single_molecule.x()),y(single_molecule.y()),CYAN);
        single_molecule.walk();
    }
    getch();
    //distribution of molecules at different times

    cleardevice();
    graph_axes();
    Molecule molecule[number_of_molecules];
    double entropy[800]={0};
    int counter[(x_max-x_min)/step_size][(y_max-y_min)/step_size]={0};
    for(int t=0; t<=2000; t++){
        if (t==10 || t==100 || t==1000 || t==2000){
            for (int i=0; i<number_of_molecules; i++){
                putpixel(x(molecule[i].x()),y(molecule[i].y()),YELLOW);
            }
            getch();
            cleardevice();
            graph_axes();
        }
        for (int i=0; i<number_of_molecules; i++){
            molecule[i].walk();
            counter[(molecule[i].x()-x_min)/step_size][(molecule[i].y()-y_min)/step_size]++;
        }


        //clear counter and measure entropy
        for (int i=0; i<(x_max-x_min)/step_size; i++){
            for (int j=0; j<(y_max-y_min)/step_size; j++){
                if (t<800 && counter[i][j]!=0)entropy[t]-=double(counter[i][j])/number_of_molecules*log(double(counter[i][j])/number_of_molecules);
                counter[i][j]=0;
            }
        }


    }
    x_min=0;
    x_max=800;
    y_min=0;
    y_max=8;

    cleardevice();
    graph_axes();

    moveto(x(0),y(0));
    setcolor(GREEN);
    double max_entropy=0.0;
    for (int t=0; t<800; t++){
        lineto(x(t),y(entropy[t]));
        if(entropy[t]>max_entropy) max_entropy=entropy[t];
    }
    setcolor(WHITE);
    line(x(0),y(max_entropy),x(799), y(max_entropy));
    outtextxy(0.75*width, 0.2*height,"Entropy vs. Time");
    sprintf(buffer,"%.6f", max_entropy);
    outtextxy(2*width/20.0,y(max_entropy),buffer);

    getch();
    return 0;
}
