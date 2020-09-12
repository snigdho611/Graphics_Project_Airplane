#include <cstdio>
#include<iostream>
#include<GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include<math.h>
//#include <X11/Xlib.h>

using namespace std;

GLfloat spx,spy,spz,tpx,tpy,tpz;

GLfloat firstForwardPosition = 0.0f;
GLfloat firstSpeed = 0.0f;
GLfloat max_firstSpeed = -1.0f;
int planeHeight=0;
int low_planeHeight=1000;

bool planeTakeofAngle=false;

GLfloat dive1_speed=0;

bool dive1=false;

GLfloat dive2_speed=0;

bool dive2=false;

GLbyte dive2_byte;

GLfloat shipForwardPosition = 0.0f;
GLfloat shipSpeed = 5.0f;
GLfloat max_shipForwardPosition = 700.0f;
GLfloat min_shipForwardPosition = -600.0f;

float _rain = 0.0;
float _nt = 0.0;

bool rainday = false;
bool night = false;

bool onLand=true;
bool landing=false;
bool landable=false;

bool flag=false;

void myDisplay2();
void myDisplay3();

void takeoff(int value) {
    if(firstSpeed < max_firstSpeed)
        firstSpeed+=0.5;
    firstForwardPosition += firstSpeed;
    if(firstSpeed==max_firstSpeed){
        planeTakeofAngle=true;
    }
    glutPostRedisplay();
    glutTimerFunc(100, takeoff, 0);
}
void shipMovement(int value){
    if(shipForwardPosition == max_shipForwardPosition || shipForwardPosition == min_shipForwardPosition){
        shipSpeed*=-1;
    }
    shipForwardPosition+=shipSpeed;
    glutPostRedisplay();
    glutTimerFunc(100, shipMovement, 0);
}
void Ship(){

    glPushMatrix();
    glTranslatef(shipForwardPosition,0,0);
        //main body
        glColor3ub(200,200,200);
        glBegin(GL_POLYGON);
            glVertex2i(-320,-80);
            glVertex2i(-500,-80);
            glVertex2i(-480,-120);
            glVertex2i(-340,-120);
        glEnd();
        glFlush();

        //hull
        glColor3ub(100,100,100);
        glBegin(GL_POLYGON);
            glVertex2i(-370,-40);
            glVertex2i(-450,-40);
            glVertex2i(-450,-80);
            glVertex2i(-370,-80);
        glEnd();
        glFlush();

        //Exhaust
        glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
            glVertex2i(-470,-20);
            glVertex2i(-480,-20);
            glVertex2i(-480,-80);
            glVertex2i(-470,-80);
        glEnd();
    glPopMatrix();
    glFlush();


}
void Plane(){
    glPushMatrix();
        if(onLand){
            tpx=300;tpy=-160;tpz=0;
        }
        glTranslatef(tpx,tpy,tpz);
        glScalef(0.4,0.4,0);
        if(planeTakeofAngle){
            glRotatef(45,-1.0,1.0,0);
            if(planeHeight < low_planeHeight){
                glTranslatef(0,planeHeight+=20,0);
            }
            else{
                glTranslatef(0,planeHeight,0);
                glRotatef(-45,-1.0,1.0,0);
                glScalef(0.8,0.8,0);
                planeTakeofAngle=false;
            }
            onLand=false;
        }
        if(dive1){
            glTranslatef(dive1_speed-=100,0,0);
            if(dive1_speed==-3600){
                glutDisplayFunc(myDisplay2);
                dive2_speed=900;
                dive1=false;
                dive2=true;
                dive2_byte=0;
            }
        }
        if(dive2){
            if(dive2_byte==0){
                dive2_speed-=20;
                tpx=dive2_speed;
                tpy=0;
                tpz=0;
                spx=1;spy=1;spz=1;
                if(dive2_speed==-400){
                    dive2_byte=1;
                }
            }
            else{
                dive2_speed+=20;
                tpx=dive2_speed;
                spx=-1;
                if(dive2_speed==300){
                    dive2_byte=0;
                    landable=true;
                    tpx=-900;
                }
            }
            glTranslatef(tpx,tpy,tpz);
            glScalef(spx,spy,spz);
        }
        if(landing){
            if(landable){
                dive2=false;
                glutDisplayFunc(myDisplay3);
                if(tpx<360)
                    tpx+=20;
                if(tpy>-400){
                    tpy-=10;
                    glRotatef(45,1,-1,0);
                }
                glTranslatef(tpx,tpy,tpz);
                glScalef(-1,1,1);
            }
        }
        //mainframe
        glBegin(GL_POLYGON);
            glColor3ub (128, 128, 128);
            glVertex2d(-140,0);
            glVertex2d(-180,-80);
            glVertex2d(360,-80);
            glVertex2d(360,0);
        glEnd();
        //WING
        glBegin(GL_POLYGON);
            glColor3ub (171, 171, 171);
            glVertex2d(-70,-40);
            glVertex2d(140,-115);
            glVertex2d(320,-115);
            glVertex2d(300,-40);
        glEnd();
        //TAIL
        glBegin(GL_POLYGON);
            glColor3ub (171, 171, 171);
            glVertex2d(280,80);
            glVertex2d(240,0);
            glVertex2d(320,0);
            glVertex2d(320,80);
        glEnd();
        //Exhaust
        glBegin(GL_POLYGON);
            glColor3ub (171, 171, 171);
            glVertex2d(380,-20);
            glVertex2d(360,-20);
            glVertex2d(360,-60);
            glVertex2d(380,-60);
        glEnd();
        //wheelstand 1
        glBegin(GL_POLYGON);
            glColor3ub (1,1,1);
            glVertex2d(-60,-80);
            glVertex2d(-55,-80);
            glVertex2d(-55,-130);
            glVertex2d(-60,-130);
        glEnd();
        glBegin(GL_POLYGON);
            glColor3ub (1,1,1);
            glVertex2d(-70,-80);
            glVertex2d(-45,-80);
            glVertex2d(-45,-87);
            glVertex2d(-70,-87);
        glEnd();
        //wheelstand2
        glBegin(GL_POLYGON);
            glColor3ub (1,1,1);
            glVertex2d(245,-115);
            glVertex2d(240,-115);
            glVertex2d(240,-130);
            glVertex2d(245,-130);
        glEnd();

        //WHEEL1
        glTranslatef(-57, -125, 0.0f);

        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

        glPolygonMode( GL_FRONT, GL_FILL );
        glBegin(GL_POLYGON);
            int r=20;
            for(int i =0; i <= 300; i++){
                double angle = 2 * 3.1416 * i / 300;
                double x =r * cos(angle);
                double y =r * sin(angle);
                glVertex2d(x,y);
         }
        glEnd();
        //WHEEL2
        glTranslatef(57, 125, 0.0f);
        glTranslatef(242, -127, 0.0f);

        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

        glPolygonMode( GL_FRONT, GL_FILL );
        glBegin(GL_POLYGON);
        //int r=10;
        for(int i =0; i <= 300; i++){
             double angle = 2 * 3.1416 * i / 300;
             double x =r * cos(angle);
             double y =r * sin(angle);
             glVertex2d(x,y);
         }
        glEnd();

        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

        glPolygonMode( GL_FRONT, GL_FILL );
        glBegin(GL_POLYGON);
        //int r=10;
        for(int i =0; i <= 300; i++){
             double angle = 2 * 3.1416 * i / 300;
             double x =r * cos(angle);
             double y =r * sin(angle);
             glVertex2d(x,y);
         }
        glEnd();
    glPopMatrix();

    glFlush();
}
void Display1(){

   //Exterior buildings
    glPushMatrix();

        int extb1 = -1270,extb2 = -1200;
        int window1 = -1195, window2 = -1155, window3 = -1195, window4 = -1155;

        for(int i=0;i<200;i++){
            glPushMatrix();
                glTranslatef(firstForwardPosition,0.0f, 0.0f);

                glColor3ub (74,5,15);
                    glBegin(GL_POLYGON);
                    glVertex2i(extb1+70, 0);
                    glVertex2i(extb1+140, 0);
                    glVertex2i(extb1+140, 200);
                    glVertex2i(extb1+70, 200);
                    extb1 = extb1+140;
                glEnd();


                glColor3ub (74,5,15);
                    glBegin(GL_POLYGON);
                    glVertex2i(extb2+70, 0);
                    glVertex2i(extb2+140, 0);
                    glVertex2i(extb2+140, 150);
                    glVertex2i(extb2+70, 150);
                    extb2 = extb2+140;
                glEnd();


                glColor3ub (192,192,192);
                glBegin(GL_QUADS);
                    glVertex2i(window1,180);
                    glVertex2i(window1,160);
                    glVertex2i(window1+15,160);
                    glVertex2i(window1+15,180);

                    glVertex2i(window2,180);
                    glVertex2i(window2,160);
                    glVertex2i(window2+15,160);
                    glVertex2i(window2+15,180);

                    glVertex2i(window3,140);
                    glVertex2i(window3,120);
                    glVertex2i(window3+15,120);
                    glVertex2i(window3+15,140);

                    glVertex2i(window4,140);
                    glVertex2i(window4,120);
                    glVertex2i(window4+15,120);
                    glVertex2i(window4+15,140);

                    window1 = window1+140;
                    window2 = window2+140;
                    window3 = window3+140;
                    window4 = window4+140;
                //glVertex2i(, 0);
                glEnd();
            glPopMatrix();

        }
    glPopMatrix();
    //Airport wall
    glColor3f (0.0, 0.2, 0.4);
    glBegin(GL_POLYGON);
        glVertex2i(-1200, -400);
        glVertex2i(640, -400);
        glVertex2i(640, 100);
        glVertex2i(-1200, 100);
    glEnd();
    glFlush();
        //Exterior concrete
    glPushMatrix();
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glColor3f (0.8, 0.8, 0.8);
        glBegin(GL_QUADS);
            glVertex2i(-1200, 0);
            glVertex2i(-1100, -360);
            glVertex2i(640, -360);
            glVertex2i(640, 0);
        glEnd();
    glPopMatrix();
    //Runway concrete
    glPushMatrix();
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        //glClear (GL_COLOR_BUFFER_BIT);
        glColor3f (0.3, 0.3, 0.3);
        glPointSize(5.0);
        glBegin(GL_POLYGON);
            glVertex2i(640, -250);
            glVertex2i(-1050, -250);
            glVertex2i(-1100, -150);
            glVertex2i(640, -150);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        int runwayx1=-1100, runwayx2=-1050;
        int lights1=runwayx1+15, lights2=runwayx2+35;
        for(int i=0;i<17;i++){
            glPushMatrix();
                glTranslatef(firstForwardPosition,0.0f, 0.0f);

                glColor3f (1.0, 1.0, 1.0);
                glBegin(GL_POLYGON);
                    glVertex2i(runwayx1, -150);
                    glVertex2i(runwayx1+50, -250);
                    glVertex2i(runwayx2+50, -250);
                    glVertex2i(runwayx2, -150);
                glEnd();

                runwayx1 = runwayx1+100;
                runwayx2 = runwayx2+100;

                if(i%2==0)glColor3f (1.0, 0.0, 0.0);
                else glColor3f (1.0, 1.0, 0.0);
                glPointSize(7.0);
                glBegin(GL_POINTS);
                glVertex2i(lights1, -153);
                glEnd();

                glPointSize(10.0);
                glBegin(GL_POINTS);
                glVertex2i(lights2, -245);
                glEnd();

                lights1=lights1+100;
                lights2=lights2+100;
            glPopMatrix();
        }
    glPopMatrix();


    //////////////////////////////////////////////////////////////runway close///////////////////////////////////////////////

 ///////////////////////////////////////////////////////
    ///Cloud---1
    glPushMatrix();
        glTranslatef(-350, 285, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
            float pi=3.1416;
            float A=(i*2*pi)/300;
            float r=35;
            float x = r * sin(A);
            float y = r * cos(A);
            glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-350, 255, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=35;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-400, 265, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=35;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-300, 265, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=35;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();
////////////////////////////////////////////////////////////
    ///Cloud---2
    glPushMatrix();
        glTranslatef(150, 275, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(155, 250, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(195, 260, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(110, 260, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();
    //SUN
    glPushMatrix();
        glColor3ub(255,200,0);
        glTranslatef(500, 300, 0.0f);

        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

        glPolygonMode( GL_FRONT, GL_FILL );
        glBegin(GL_POLYGON);
            int r1=45;
            for(int i =0; i <= 300; i++){
                double angle = 2 * 3.1416 * i / 300;
                double x =r1 * cos(angle);
                double y =r1 * sin(angle);
                glVertex2d(x,y);
         }
        glEnd();
    glPopMatrix();

    //Airport buildings
    glPushMatrix();
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glColor3f (0.9, 0.9, 0.9);
        glBegin(GL_POLYGON);
            glVertex2i(-500, 50);
            glVertex2i(-500, -50);
            glVertex2i(-300, -50);
            glVertex2i(-300, 50);
            glVertex2i(-400, 80);
        glEnd();


        glColor3f (0.5, 0.5, 0.5);
        glBegin(GL_QUADS);
            glVertex2i(-480,30);
            glVertex2i(-480,-40);
            glVertex2i(-320,-40);
            glVertex2i(-320,30);
        glEnd();
    glPopMatrix();

}
void Display2(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();
    glBegin(GL_QUADS);
        glColor3ub(0, 105, 148	);
        glVertex2i(640,-50);
        glVertex2i(-640,-50);
        glVertex2i(-640,-360);
        glVertex2i(640,-360);
    glEnd();
    glFlush();

    Ship();

    //SUN
    glPushMatrix();
        glColor3ub(255,200,0);
        glTranslatef(500, 300, 0.0f);

        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

        glPolygonMode( GL_FRONT, GL_FILL );
        glBegin(GL_POLYGON);
            int r1=45;
            for(int i =0; i <= 300; i++){
             double angle = 2 * 3.1416 * i / 300;
             double x =r1 * cos(angle);
             double y =r1 * sin(angle);
             glVertex2d(x,y);
         }
        glEnd();
    glPopMatrix();

    //BIRDS
    glColor3f(0.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(60,20,0);
    glBegin(GL_POLYGON);
        glVertex2i(220,160);
        glVertex2i(240,170);
        glVertex2i(220,150);
        glVertex2i(200,170);
    glEnd();
    glPopMatrix();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2i(220,160);
        glVertex2i(240,170);
        glVertex2i(220,150);
        glVertex2i(200,170);
    glEnd();
    glFlush();
}
void Display3(){
    //Exterior buildings
    glPushMatrix();

        int extb1 = -1270,extb2 = -1200;
        int window1 = -1195, window2 = -1155, window3 = -1195, window4 = -1155;

        for(int i=0;i<200;i++){
            glPushMatrix();
                glTranslatef(0.0f,0.0f, 0.0f);

                glColor3ub (74,5,15);
                    glBegin(GL_POLYGON);
                    glVertex2i(extb1+70, 0);
                    glVertex2i(extb1+140, 0);
                    glVertex2i(extb1+140, 200);
                    glVertex2i(extb1+70, 200);
                    extb1 = extb1+140;
                glEnd();


                glColor3ub (74,5,15);
                    glBegin(GL_POLYGON);
                    glVertex2i(extb2+70, 0);
                    glVertex2i(extb2+140, 0);
                    glVertex2i(extb2+140, 150);
                    glVertex2i(extb2+70, 150);
                    extb2 = extb2+140;
                glEnd();


                glColor3ub (192,192,192);
                glBegin(GL_QUADS);
                    glVertex2i(window1,180);
                    glVertex2i(window1,160);
                    glVertex2i(window1+15,160);
                    glVertex2i(window1+15,180);

                    glVertex2i(window2,180);
                    glVertex2i(window2,160);
                    glVertex2i(window2+15,160);
                    glVertex2i(window2+15,180);

                    glVertex2i(window3,140);
                    glVertex2i(window3,120);
                    glVertex2i(window3+15,120);
                    glVertex2i(window3+15,140);

                    glVertex2i(window4,140);
                    glVertex2i(window4,120);
                    glVertex2i(window4+15,120);
                    glVertex2i(window4+15,140);

                    window1 = window1+140;
                    window2 = window2+140;
                    window3 = window3+140;
                    window4 = window4+140;
                //glVertex2i(, 0);
                glEnd();
            glPopMatrix();

        }
    glPopMatrix();
    //Airport wall
    glColor3f (0.0, 0.2, 0.4);
    glBegin(GL_POLYGON);
        glVertex2i(-1200, -400);
        glVertex2i(640, -400);
        glVertex2i(640, 100);
        glVertex2i(-1200, 100);
    glEnd();
    glFlush();
        //Exterior concrete
    glPushMatrix();
        glTranslatef(0.0f,0.0f, 0.0f);
        glColor3f (0.8, 0.8, 0.8);
        glBegin(GL_QUADS);
            glVertex2i(-1200, 0);
            glVertex2i(-1100, -360);
            glVertex2i(640, -360);
            glVertex2i(640, 0);
        glEnd();
    glPopMatrix();
    //Runway concrete
    glPushMatrix();
        glTranslatef(0.0f,0.0f, 0.0f);
        //glClear (GL_COLOR_BUFFER_BIT);
        glColor3f (0.3, 0.3, 0.3);
        glPointSize(5.0);
        glBegin(GL_POLYGON);
            glVertex2i(640, -250);
            glVertex2i(-1050, -250);
            glVertex2i(-1100, -150);
            glVertex2i(640, -150);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        int runwayx1=-1100, runwayx2=-1050;
        int lights1=runwayx1+15, lights2=runwayx2+35;
        for(int i=0;i<17;i++){
            glPushMatrix();
                glTranslatef(0.0f,0.0f, 0.0f);

                glColor3f (1.0, 1.0, 1.0);
                glBegin(GL_POLYGON);
                    glVertex2i(runwayx1, -150);
                    glVertex2i(runwayx1+50, -250);
                    glVertex2i(runwayx2+50, -250);
                    glVertex2i(runwayx2, -150);
                glEnd();

                runwayx1 = runwayx1+100;
                runwayx2 = runwayx2+100;

                if(i%2==0)glColor3f (1.0, 0.0, 0.0);
                else glColor3f (1.0, 1.0, 0.0);
                glPointSize(7.0);
                glBegin(GL_POINTS);
                glVertex2i(lights1, -153);
                glEnd();

                glPointSize(10.0);
                glBegin(GL_POINTS);
                glVertex2i(lights2, -245);
                glEnd();

                lights1=lights1+100;
                lights2=lights2+100;
            glPopMatrix();
        }
    glPopMatrix();


    //////////////////////////////////////////////////////////////runway close///////////////////////////////////////////////

 ///////////////////////////////////////////////////////
    ///Cloud---1
    glPushMatrix();
        glTranslatef(-350, 285, 0);
        glTranslatef(0.0f,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
            float pi=3.1416;
            float A=(i*2*pi)/300;
            float r=35;
            float x = r * sin(A);
            float y = r * cos(A);
            glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-350, 255, 0);
        glTranslatef(0.0f,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=35;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-400, 265, 0);
        glTranslatef(0.0f,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=35;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-300, 265, 0);
        glTranslatef(0.0f,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=35;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();
////////////////////////////////////////////////////////////
    ///Cloud---2
    glPushMatrix();
        glTranslatef(150, 275, 0);
        glTranslatef(0.0f,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(155, 250, 0);
        glTranslatef(0.0f,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(195, 260, 0);
        glTranslatef(0.0f,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(110, 260, 0);
        glTranslatef(0.0f,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();
    //SUN
    glPushMatrix();
        glColor3ub(255,200,0);
        glTranslatef(500, 300, 0.0f);

        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

        glPolygonMode( GL_FRONT, GL_FILL );
        glBegin(GL_POLYGON);
            int r1=45;
            for(int i =0; i <= 300; i++){
                double angle = 2 * 3.1416 * i / 300;
                double x =r1 * cos(angle);
                double y =r1 * sin(angle);
                glVertex2d(x,y);
         }
        glEnd();
    glPopMatrix();

    //Airport buildings
    glPushMatrix();
        glTranslatef(0.0f,0.0f, 0.0f);
        glColor3f (0.9, 0.9, 0.9);
        glBegin(GL_POLYGON);
            glVertex2i(-500, 50);
            glVertex2i(-500, -50);
            glVertex2i(-300, -50);
            glVertex2i(-300, 50);
            glVertex2i(-400, 80);
        glEnd();


        glColor3f (0.5, 0.5, 0.5);
        glBegin(GL_QUADS);
            glVertex2i(-480,30);
            glVertex2i(-480,-40);
            glVertex2i(-320,-40);
            glVertex2i(-320,30);
        glEnd();
    glPopMatrix();

}
void Rain(int value){

    if(rainday){

        _rain += 0.01f;

        glBegin(GL_LINES);
        glPointSize(0.05f);
        for(int i=1;i<=100;i++)
        {
            int x=rand()%1281-640,y=rand()%736-330;
            x%=10000; y%=10000;

            glColor3f(1.0, 1.0, 1.0);
            glVertex2d(x,y);
            glVertex2d(x+3,y+3);
            glEnd();
        }

            ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Cloud
        glPushMatrix();
            glTranslatef(150+340, 275+20, 0);
            glBegin(GL_POLYGON);
                glColor3f(.3,.3,.3);
                for(int i=0;i<300;i++){
                    float pi=3.1416;
                    float A=(i*2*pi)/300;
                    float r=30;
                    float x = r * sin(A);
                    float y = r * cos(A);
                    glVertex2f(x,y );
            }
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(155+340, 250+20, 0);
            glBegin(GL_POLYGON);
                glColor3f(.3,.3,.3);
                for(int i=0;i<300;i++){
                    float pi=3.1416;
                    float A=(i*2*pi)/300;
                    float r=30;
                    float x = r * sin(A);
                    float y = r * cos(A);
                    glVertex2f(x,y );
            }
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(195+340, 260+20, 0);
            glBegin(GL_POLYGON);
                glColor3f(.3,.3,.3);
                for(int i=0;i<300;i++){
                    float pi=3.1416;
                    float A=(i*2*pi)/300;
                    float r=30;
                    float x = r * sin(A);
                    float y = r * cos(A);
                    glVertex2f(x,y );
            }
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(110+345, 260+20, 0);
            glBegin(GL_POLYGON);
                glColor3f(.3,.3,.3);
                for(int i=0;i<300;i++){
                    float pi=3.1416;
                    float A=(i*2*pi)/300;
                    float r=30;
                    float x = r * sin(A);
                    float y = r * cos(A);
                    glVertex2f(x,y );
            }
            glEnd();
        glPopMatrix();

        glutPostRedisplay();
        glutTimerFunc(100, Rain, 0);

        glFlush();

        ///Cloud---1
    glPushMatrix();
        glTranslatef(-350, 285, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(.3,.3,.3);
            for(int i=0;i<300;i++){
            float pi=3.1416;
            float A=(i*2*pi)/300;
            float r=35;
            float x = r * sin(A);
            float y = r * cos(A);
            glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-350, 255, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(.3,.3,.3);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=35;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-400, 265, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(.3,.3,.3);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=35;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-300, 265, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(.3,.3,.3);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=35;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();
////////////////////////////////////////////////////////////
    ///Cloud---2
    glPushMatrix();
        glTranslatef(150, 275, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(.3,.3,.3);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(155, 250, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(.3,.3,.3);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(195, 260, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(.3,.3,.3);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(110, 260, 0);
        glTranslatef(firstForwardPosition,0.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(.3,.3,.3);
            for(int i=0;i<300;i++){
                float pi=3.1416;
                float A=(i*2*pi)/300;
                float r=30;
                float x = r * sin(A);
                float y = r * cos(A);
                glVertex2f(x,y );
        }
        glEnd();
    glPopMatrix();
    //SUN
    glPushMatrix();
        glColor3ub(200,200,200);
        glTranslatef(500, 300, 0.0f);

        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

        glPolygonMode( GL_FRONT, GL_FILL );
        glBegin(GL_POLYGON);
            int r1=45;
            for(int i =0; i <= 300; i++){
                double angle = 2 * 3.1416 * i / 300;
                double x =r1 * cos(angle);
                double y =r1 * sin(angle);
                glVertex2d(x,y);
         }
        glEnd();
    glPopMatrix();

    }
}
void Night(int value){

    if(night){
        glColor3f(0.10, 0.10, 0.10);

        glPushMatrix();
            glColor3f(1,1,1);
            glTranslatef(500, 300, 0.0f);

            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

            glPolygonMode( GL_FRONT, GL_FILL );
            glBegin(GL_POLYGON);
                int r1=45;
                for(int i =0; i <= 300; i++){
                 double angle = 2 * 3.1416 * i / 300;
                 double x =r1 * cos(angle);
                 double y =r1 * sin(angle);
                 glVertex2d(x,y);
             }
            glEnd();
        glPopMatrix();

        glClearColor(0.0,0.0,0.0,0.0);
        glutPostRedisplay();
        glutTimerFunc(100, Night, 0);
        glFlush();

    }
}
void myDisplay1(void){
    glClear(GL_COLOR_BUFFER_BIT);
    Display1();
    Plane();
}
void myDisplay2(void){
    glClear(GL_COLOR_BUFFER_BIT);
    Display2();
    Plane();
}
void myDisplay3(void){
    glClear(GL_COLOR_BUFFER_BIT);
    Display3();
    Plane();
    Rain(0);
    Night(0);
}
void myInit(void){
    glClearColor(0.1, 0.8, 1, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-640.0, 640.0, -360.0, 360.0);
}
void handleKeypress(unsigned char key, int x, int y) {

	switch (key) {

        case ' ':
            firstSpeed = 1.0f;
            max_firstSpeed = 30.0f;
            break;
        case 'w':
            planeHeight+=2;
            break;
        case 's':
            planeHeight-=2;
            break;
        case 'r':
            if(rainday)
                rainday=false;
            else
                rainday=true;
            break;
        case 'n':
            if(night)
                night=false;
            else
                night=true;
            break;
        case '2':
            dive1=true;
            break;
        case 'l':
            landing=true;
            break;

        glutPostRedisplay();
	}
}

int main(int argc, char** argv){
    cout << endl << "*********** Plane Takeoff and Landing Scenario ********************" << endl << endl;

    cout << "Press Space : To Take off the plane" << endl << endl;
    cout << "Press    l    : To Land" << endl << endl;
    cout << "Press    2    : For A Tour " << endl << endl;
    cout << "Press    n    : For Night (only after landing) " << endl << endl;
    cout << "Press    r    : For Rain (only after landing or before landing)" << endl << endl;
    cout << "Press r again : To Stop Rain (only after landing or before landing)" << endl << endl;


    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (1280, 720);
    glutInitWindowPosition (5, 5);
    glutCreateWindow ("");
    myInit ();
    glutDisplayFunc(myDisplay1);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(100,takeoff,0);
    glutTimerFunc(100,shipMovement,0);
    glutMainLoop();
}
