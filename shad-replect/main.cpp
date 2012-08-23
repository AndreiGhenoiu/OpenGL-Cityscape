//#include <windows.h>
//Program by Andrei Ghenoiu
//Fall 2011 - Vermont Technical College - Computer Graphics
//contact me at andrei_stefang@yahoo.com if you have any questions

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include "header.h"

static float rot = 0;
static float x1 = 0;
static float change = 0.2;
static float carMov = 0.2;
static float yAxis;
static float xAxis;
static float pointX;
static float pointY;
static float sc = 1;
GLfloat cube_color[4] = {1,0,0,1};
GLuint texture1;
GLuint texture2;
GLuint texture3;
GLuint texture4;
GLuint texture5;
GLuint water;
GLuint asphalt;
GLuint grass;

//car coordinates
float xCoord = 0;
float zCoord = 10;

void controlRotate(unsigned char key,int x,int y){

    switch(key){

        case 'w':
            yAxis+=change;
           // printf("moving");
            break;
        case 's':
            yAxis-=change;
           // printf("moving");
            break;
        case 'q':
            xAxis -= change;
            break;
        case 'e':
            xAxis += change;
            break;
        case 'd':
            rot += change;
            break;
        case 'a':
            rot -= change;
            break;

        case 'p':
            sc +=change/10;
            break;
        case 'o':
            sc -=change/10;
            break;
        //changes in lighting

    }

}
void applyMat(float R, float G, float B){
    GLfloat cube_color[4] = {R, G, B,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, cube_color);
}
void rotate(){

    zCoord-=carMov/2;
    if(zCoord < 0){
        carMov -=carMov/50;
    }
    glutPostRedisplay();
}

//maybe a function to create the town
void display()
{
     glEnable( GL_TEXTURE_2D );
     //glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPONENTS, &value);

    texture1 = LoadTexture( "building.raw", 256, 256 );
    texture2 = LoadTexture("texture3.raw",256,256);
    texture3 = LoadTexture( "building3.raw", 256, 256 );
    texture4 = LoadTexture( "texture5.raw", 256, 256 );
    texture5 = LoadTexture( "texture6.raw", 256, 256 );

    asphalt = LoadTexture( "asphalt.raw", 256, 256 );
    water = LoadTexture( "water.raw", 256, 256 );
    grass = LoadTexture( "grass.raw", 256, 256 );

    reflect1();

    gluLookAt(0,yAxis,-5,0,0,0,0,1,0);
    glTranslatef(xAxis,0,0);
    glScalef(sc, sc, sc);
    glRotatef(rot*2,0,1,0);

    createPool();

    reflect2();

    //reflected buildings start here
    createBuilding(-1,0,-2,2,6, texture5);
    createBuilding(2,1,0,0,3, texture3);
    createBuilding(0,-1,1,-2,2, texture1);
    //world trade
    createBuilding(-2,3,-4,5,10,texture1);
    createBuilding(-7,8,-5,6,10,texture1);

    createBuilding(-2,-2,-1,-1,6, texture3);
    createBuilding(2,-1,3,-3,6.5,texture2);
    createBuilding(3,-1,4,-2,4,texture3);
    createBuilding(7,-2,9,-5,4,texture5);
    createBuilding(0,3,1,5,6,texture1);
    createBuilding(1,4,2,5,3,texture5);
    createBuilding(2,3,3,5,6,texture1);
    createBuilding(-2,-4,-1,-5,2,texture4);
    createBuilding(0,-4,2,-5,1,texture2);
    createBuilding(-5,-1,-3,-2,8, texture4);
    createBuilding(0,8,6,6,2,texture1);
    createBuilding(8,3,9,-1,1,texture3);
    createBuilding(-4,2,-3,0,5,texture2);
    createBuilding(-9,-3,-10,-1,6,texture3);
    createBuilding(-7,-4,-8,-1,5,texture2);
    createBuilding(-5,-9,-4,-10,4,texture4);
    createBuilding(1,-8,6,-10,2,texture3);
    createBuilding(6,-8,8,-9,1,texture4);
    createBuilding(8,-8,9,-10,2,texture3);
    createBuilding(-9,-7,-7,-9,5,texture5);
    createBuilding(-9,2,-5,1,5,texture1);
    createBuilding(-8,1,-6,0,2,texture3);
    createBuilding(-9,5,-8,3,4,texture3);
    createBuilding(7,8,9,6,4,texture5);


    glPopMatrix();

    glEnable(GL_DEPTH_TEST); //enable the depth testing
    glDisable(GL_STENCIL_TEST); //disable the stencil testing
    glEnable(GL_BLEND); //enable alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set the blending function

    createPool();

    glDisable(GL_BLEND); //disable alpha blending
    createPlane(grass);
    glEnable(GL_LIGHTING);

    //actual buildings start here
    createBuilding(-1,0,-2,2,6, texture5);
    createBuilding(2,1,0,0,3, texture3);
    createBuilding(0,-1,1,-2,2, texture1);
    //world trade
    createBuilding(-2,3,-4,5,10,texture1);
    createBuilding(-7,8,-5,6,10,texture1);

    createBuilding(-2,-2,-1,-1,6, texture3);
    createBuilding(2,-1,3,-3,6.5,texture2);
    createBuilding(3,-1,4,-2,4,texture3);
    createBuilding(7,-2,9,-5,4,texture5);
    createBuilding(0,3,1,5,6,texture1);
    createBuilding(1,4,2,5,3,texture5);
    createBuilding(2,3,3,5,6,texture1);
    createBuilding(-2,-4,-1,-5,2,texture4);
    createBuilding(0,-4,2,-5,1,texture2);
    createBuilding(-5,-1,-3,-2,8, texture4);
    createBuilding(0,8,6,6,2,texture1);
    createBuilding(8,3,9,-1,1,texture3);
    createBuilding(-4,2,-3,0,5,texture2);
    createBuilding(-9,-3,-10,-1,6,texture3);
    createBuilding(-7,-4,-8,-1,5,texture2);
    createBuilding(-5,-9,-4,-10,4,texture4);
    createBuilding(1,-8,6,-10,2,texture3);
    createBuilding(6,-8,8,-9,1,texture4);
    createBuilding(8,-8,9,-10,2,texture3);
    createBuilding(-9,-7,-7,-9,5,texture5);
    createBuilding(-9,2,-5,1,5,texture1);
    createBuilding(-8,1,-6,0,2,texture3);
    createBuilding(-9,5,-8,3,4,texture3);
    createBuilding(7,8,9,6,4,texture5);

    //car
    createCar(xCoord,zCoord,xCoord-.3,zCoord+.5,.5);
    createCar(xCoord-.6,zCoord+1,xCoord-.3, zCoord+1.5,.5);

    //streets
    createStreet(-1,10,0,-10,asphalt);
    createStreet(-10,0,4,-1,asphalt);
    createStreet(-2,10,-1,2,asphalt);
    createStreet(-10,2,4,3,asphalt);
    createStreet(3,0,4,2,asphalt);
    createStreet(-10,-5,10,-7,asphalt);
    createStreet(-10,6,10,5,asphalt);
    createStreet(-5,10,-4,0,asphalt);
    createStreet(9,5,10,-5,asphalt);
    createStreet(-6,-1,-5,-10,asphalt);
    createStreet(0,9,7,8,asphalt);
    createStreet(6,8,7,6,asphalt);
    createStreet(-8,9,0,8,asphalt);
    createStreet(-9,9,-7,3,asphalt);

    glDisable(GL_LIGHTING);
     FreeTexture(texture1);
     FreeTexture(texture2);
     FreeTexture(texture3);
     FreeTexture(texture4);
     FreeTexture(texture5);
     FreeTexture(asphalt);
     FreeTexture(water);
     FreeTexture(grass);

   glutSwapBuffers();
}


void init()
{

    GLfloat light_pos[4] = { 13,15,15,0};
    GLfloat ambient_color[4] = { .8,.8,.8,1};

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel (GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, 1, 0.1, 1000.0);
    glMatrixMode (GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT, ambient_color);

  glutKeyboardFunc(controlRotate);
}

int main(int argc,char ** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(500,500);
  glutCreateWindow("simple");
  glutIdleFunc(rotate);
  glutDisplayFunc(display);
  init();

  glutMainLoop();
  return 0;
}
