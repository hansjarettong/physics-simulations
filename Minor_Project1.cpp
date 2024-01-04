//Precession of the Perihelion of Mercury
#include<iostream>
#include<cmath>
#include<graphics.h>
#include<stdio.h>

using namespace std;

double width=600.0;// window width in pixels
double height=600.0;// window height in pixels
double x_range=1.2; // the range of x in astronomical units (AU)
double y_range=1.2; // the range of y in astronomical units (AU)
double x_scale=width/x_range;// scale of x in pixel per AU
double y_scale=height/y_range;// scale of y in pixel per AU
const int number_of_perihelia= 10; //DON'T CHANGE THIS!!! the number of number_of_perihelia.

double delta_t=1e-4;

double alpha[10];

void initalpha(){
    for(int k=0; k<10; k++){
        alpha[k]=0.0002+0.0003*k;
    }
}

double x(double _x){
    return (width/2.0)+_x*x_scale;
}//convert from Cartesian to c++ convention

double y(double _y){
    return (height/2.0)-_y*y_scale;
}//convert from Cartesian to c++ convention

double plot_t(double _t, double max_t){
    return 4*width/5*_t/max_t+width/10.0;
}//scales t for plotting- converts to c++ convention.
//We can also use this for plotting alpha

double plot_theta(double _theta, double max_theta){
    return -17*height/30*_theta/max_theta+9*height/10.0;
}//scales theta for plotting- converts to c++ convention

double plot_rate(double _rate, double max_rate){
    return -4*height/5*_rate/max_rate+9*height/10;
}

double least_squares_slope(double _array[10][2]){
    double sum_xy=0.0;
    double sum_x=0.0;
    double sum_y=0.0;
    double sum_x2=0.0;
    for (int i=0; i<number_of_perihelia; i++){
        sum_xy+=_array[i][0] *_array[i][1];
        sum_x+=_array[i][0];
        sum_y+=_array[i][1];
        sum_x2+=_array[i][0]*_array[i][0];
    }
    return (number_of_perihelia*sum_xy-sum_x*sum_y)/(number_of_perihelia*sum_x2-sum_x*sum_x);
}// this can only accept a static array of dimensions [10][2]. That's why we set number_of_perihelia=10
// and it so happens that alpha also has 10 elements.


class Planet{
private:
    double x=0.47;//x-position of the planet, initially set to 0.47
    double y=0.0;//y-position of the planet, initially set to 0.0
    double v_x=0.0; //x-component of the velocity, initially set yo 0.0
    double v_y=8.2;// y-component of the velocity, initially set to 8.2
    double t=0.0;// tells the current time, initially set to 0.0
    double alpha=0.0002;// as given in the formula. In AU^2

    //the x and y components of the perihelion
    double perihelion_x=x;
    double perihelion_y=y;

    bool was_increasing= false;
    bool is_increasing= false;

    //temporary variables for holding current r
    double prev_r;

    double r(){
        return sqrt(x*x+y*y);
    }

    //I'll use _x and _y as arguments because x and y are already taken
    double a_x (double _x){
        return -4.0*M_PI*M_PI*_x/(r()*r()*r())*(1+alpha/(r()*r()));
    }// x-component of the acceleration given in AU/year^2
    double a_y (double _y){
        return -4.0*M_PI*M_PI*_y/(r()*r()*r())*(1+alpha/(r()*r()));
    }// y-component of the acceleration given in AU/year

public:
    void update_time(){
        prev_r=r();
        v_x+=a_x(x)*delta_t;
        v_y+=a_y(y)*delta_t;
        x+=v_x*delta_t;
        y+=v_y*delta_t;
        t+=delta_t;

        //get the local maximum for the perihelion
        was_increasing=is_increasing;
        if(r()-prev_r>0) is_increasing=true;
        else is_increasing=false;
        if(was_increasing==true && is_increasing==false){
            perihelion_x=x;
            perihelion_y=y;
        }
    }// allow time to move by one time step. We'll be using Euler-Cromer method
    bool is_in_perihelion(){
        return was_increasing==true && is_increasing==false;
    }//to make sure that perihelion lines are drawn only once
    double current_x(){
        return x;
    }
    double current_y(){
        return y;
    }
    double current_time(){
        return t;
    }
    double get_perihelion_x(){
        return perihelion_x;
    }
    double get_perihelion_y(){
        return perihelion_y;
    }
    double get_alpha(){
        return alpha;
    }
    void reset(){
        x=0.47;
        y=0.0;
        v_x=0.0;
        v_y=8.2;
        t=0.0;
        perihelion_x=x;
        perihelion_y=y;
        was_increasing=false;
        is_increasing=false;
    }
    void set_alpha(double a){
        alpha=a;
    }
    double get_theta(){
        return atan(y/x)*180/M_PI;
    }
};

void graph_grid(){
    line(width/2,0,width/2, height);
    line(0,height/2,width, height/2);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    settextstyle(5, HORIZ_DIR, 3);
    outtextxy(width/2,height/20,"Precession of the Perihelion of Mercury");
    setcolor(YELLOW);
    circle(x(0),y(0),width/40.0);
    setfillstyle(SOLID_FILL,YELLOW);
    floodfill(x(0),y(0),YELLOW);
    setcolor(CYAN);
    settextjustify(RIGHT_TEXT, BOTTOM_TEXT);
    settextstyle(10, HORIZ_DIR, 3);
    outtextxy(19*width/20,19*height/20,"Press any key to continue");
    setcolor(WHITE);
}

void graph_theta_time(){
    setcolor(WHITE);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    settextstyle(5, HORIZ_DIR, 3);
    outtextxy(width/2,height/20,"Precession of the Perihelion of Mercury");
    setcolor(CYAN);
    settextjustify(LEFT_TEXT,TOP_TEXT);
    settextstyle(3, HORIZ_DIR, 2);
    outtextxy(width/20,height/10,"Angle of Precession vs time");
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    settextstyle(5,VERT_DIR, 3);
    outtextxy(3*width/40,height*2/3,"theta (degrees)");
    settextstyle(3,HORIZ_DIR,2);
    outtextxy(3*width/40,19*height/20, "0");
    outtextxy(width/2, 19*height/20, "time (years)");
    line(width/10,9*height/10,9*width/10,height/3);
    setcolor(WHITE);
    settextjustify(CENTER_TEXT,BOTTOM_TEXT);
    settextstyle(3,HORIZ_DIR,2);
    outtextxy(width/2,3*width/10,"Press any key to continue");
    line(width/10,height/3,width/10,9*height/10);
    line(width/10,9*height/10,9*width/10,9*height/10);
    line(9*width/10,9*height/10,9*width/10,height/3);
    line(9*width/10,height/3,width/10,height/3);

}//this graphs the second screen (theta vs time).

void graph_rate_alpha(){
    setcolor(WHITE);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    settextstyle(5, HORIZ_DIR, 3);
    outtextxy(width/2,height/20,"Precession of the Perihelion of Mercury");
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    settextstyle(5,VERT_DIR, 3);
    outtextxy(3*width/40,height/2,"Rate of Precession (degrees/year)");
    settextstyle(3,HORIZ_DIR,2);
    outtextxy(3*width/40,19*height/20, "0");
    outtextxy(width/2, 19*height/20, "Alpha");
    settextjustify(CENTER_TEXT,TOP_TEXT);
    settextstyle(3, HORIZ_DIR, 2);
    outtextxy(width/2,height/10,"Rate of Precession vs Alpha");
    line(width/10,height/10,width/10,9*height/10);
    line(width/10,9*height/10,9*width/10,9*height/10);
    line(9*width/10,9*height/10,9*width/10,height/10);
    line(9*width/10,height/10,width/10,height/10);
    line(width/10,9*height/10,9*width/10,height/10);


}// this graphs the rate of precession vs alpha



int main(){
    //initialize stuff
    char buffer[100];
    Planet mercury;
    initalpha();
    double theta_vs_time[number_of_perihelia][2];// this should be declared dynamically
    double slope;
    double slopes[10];
    double rate_vs_alpha[10][2];
    int l=0;

    initwindow(width, height);


    for(int k=0; k<10; k++){
        //graph the orbit with the perihelion
        graph_grid();
        mercury.set_alpha(alpha[k]);
        sprintf(buffer, "Alpha = %.6f", mercury.get_alpha());
        settextjustify(LEFT_TEXT,BOTTOM_TEXT);
        outtextxy(width/20,9*height/10,buffer);
        moveto(x(mercury.current_x()),y(mercury.current_y()));
        l=0;
        while(l<number_of_perihelia){
                lineto(x(mercury.current_x()),y(mercury.current_y()));
                mercury.update_time();
                if (mercury.is_in_perihelion() && l<number_of_perihelia){
                    line(x(0),y(0),x(mercury.get_perihelion_x()),y(mercury.get_perihelion_y()));
                    //store the points of perihelion for plotting
                    theta_vs_time[l][0]=mercury.current_time();
                    theta_vs_time[l][1]=mercury.get_theta();
                    l++;
                }
        }

        getch();
        cleardevice();

        //graph theta_vs_time
        graph_theta_time();
        setcolor(YELLOW);
        for (int i=0; i<number_of_perihelia;i++){
            circle(plot_t(theta_vs_time[i][0],theta_vs_time[number_of_perihelia-1][0]),plot_theta(theta_vs_time[i][1],theta_vs_time[number_of_perihelia-1][1]),width/100);
        }

        setcolor(CYAN);
        settextjustify(LEFT_TEXT,TOP_TEXT);
        settextstyle(3, HORIZ_DIR, 2);
        outtextxy(width/2,3*height/20,buffer);


        slope=least_squares_slope(theta_vs_time);
        slopes[k]=slope;

        sprintf(buffer,"m = %.6f",slope);
        outtextxy(width/2,height/10, buffer);
        sprintf(buffer,"%.6f",theta_vs_time[number_of_perihelia-1][0]);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(9*width/10, 19*height/20, buffer);
        sprintf(buffer, "%.6f", theta_vs_time[number_of_perihelia-1][1]);
        settextjustify(CENTER_TEXT,BOTTOM_TEXT);
        outtextxy(width/10,height/3, buffer);
        setcolor(WHITE);
        getch();
        cleardevice();
        mercury.reset();
    }

    //graph rate of precession vs alpha
    graph_rate_alpha();
    setcolor(YELLOW);
    for (int i=0; i<10; i++){
        circle(plot_t(alpha[i],alpha[9]),plot_rate(slopes[i],slopes[9]),width/100);
        rate_vs_alpha[i][0]=alpha[i];
        rate_vs_alpha[i][1]=slopes[i];
    }
    slope=least_squares_slope(rate_vs_alpha);
    setcolor(WHITE);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    sprintf(buffer,"m = %.6f", slope);
    outtextxy(width/2, 3*height/20, buffer);
    sprintf(buffer,"%.6f",rate_vs_alpha[9][0]);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(9*width/10, 19*height/20, buffer);
    sprintf(buffer, "%.6f", rate_vs_alpha[9][1]);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    outtextxy(width/10,height/10, buffer);
    setcolor(CYAN);
    settextjustify(RIGHT_TEXT,TOP_TEXT);
    sprintf(buffer,"The Precession Rate for Alpha = 1.1E-8");
    outtextxy(9*width/10, 3*height/4, buffer);
    sprintf(buffer,"is %.6f degrees/year", 1.1e-8*slope);
    outtextxy(9*width/10, 3*height/4+height/20, buffer);
    sprintf(buffer, "~ %.6f arcseconds/century", 1.1e-8*slope*360000);
    outtextxy(9*width/10, 3*height/4+height/10, buffer);
    getch();
    return 0;
}
