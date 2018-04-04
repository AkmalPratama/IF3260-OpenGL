#include <stdio.h>
#include<iostream>
//#include<conio.h>
#include <stdarg.h>
#include <math.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>
//#include <GL/freeglut_ext.h>
// Function Prototypes
/* 
void display();
void Keys();
void mouse();
void MouseWheel();
*/ 
// Global Variables
bool fullscreen = false;
bool mouseDown = false;
 
float yrot=0.0f; 
float xrot=0.0f;
static double zoom=0.5;

float xdiff = 0.0f;
float ydiff = 0.0f;
 
bool init()
{
glClearColor(0.93f, 0.93f, 0.93f, 0.0f);
 
/*glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_EQUAL);
glClearDepth(1.0f);*/
 
return true;
}

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius)
{
  int i;
  int triangleAmount = 1000; 
  GLfloat twicePi = 2.0f * M_PI;

  glEnable(GL_LINE_SMOOTH);
  glLineWidth(5.0);

  glBegin(GL_LINES);
  glColor4f(1.0, 0.0, 0.0, 1.0);
  for(i = 0; i <= triangleAmount; i++)
  {
    glVertex3f( x, y, z);
    glVertex3f(x , y + (radius * cos(i * twicePi / triangleAmount)), z + (radius * sin(i * twicePi / triangleAmount)));
  }
  glEnd();
}

void DrawCylinder(float R1, float R2, float H) {
 int    i, j, steps = 32;
 float  phi, dphi = 2.*M_PI / (float)(steps);
 
 /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-10., 10., -10., 10., 1., 100.);
 
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(10., 10., 5., 0., 0., 0., 0., 0., 1.);
 
 glEnable(GL_DEPTH_TEST);
 glShadeModel(GL_FLAT);
 */
 glBegin(GL_TRIANGLE_STRIP);
 
 for(i = 0, phi = 0.; i <= steps; i ++, phi += dphi) {
 
        if((i%2) == 0)
                glColor3f(1.0, 0., 0.);
        else
                glColor3f(0., 1.0, 0.);
 
        glVertex3f(-H/2., R1*cos(phi), R1*sin(phi));
        glVertex3f(H/2., R2*cos(phi), R2*sin(phi)); }
 
 glEnd(); 
}
// display() Callback function
 
void display()
{
 
  //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
  // Reset transformations
  glLoadIdentity();
 
  // Other Transformations
  //glTranslatef( 0.3, 0.0, 0.0 );      
  //glRotatef( 180, 0.0, 1.0, 0.0 );    
 
  // Rotate when user changes xrot and yrot
  glRotatef( xrot, 1.0, 0.0, 0.0 );
  glRotatef( yrot, 0.0, 1.0, 0.0 );
 
  //Zoom in and out according to mouse wheel movement
  glScalef(zoom, zoom, zoom);
 
  // Other Transformations
  //glScalef( 1.5, 1.5, 0.0 );          // Not included
 
  //Alas mobil  
  glBegin(GL_POLYGON);
 
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(  0.25, 0.0, -0.5 );
  glVertex3f(  -0.25, 0.0, -0.5 );
  glVertex3f(  -0.25, 0.0, 0.5 );
  glVertex3f(  0.25, 0.0, 0.5 );

  glEnd();

  //bumper
  glBegin(GL_POLYGON);
  glVertex3f( 0.25, 0.0, -0.5);
  glVertex3f( 0.25, 0.1, -0.5);
  glVertex3f( -0.25, 0.1, -0.5);
  glVertex3f( -0.25, 0.0, -0.5);
  glEnd();

  //kap depan
  glBegin(GL_POLYGON);
  glVertex3f( 0.25, 0.1, -0.5);
  glVertex3f( 0.25, 0.15, -0.2);
  glVertex3f( -0.25, 0.15, -0.2);
  glVertex3f( -0.25, 0.1, -0.5);
  glEnd();

  //Kaca depan

  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 0.0);
  glVertex3f( 0.25, 0.15, -0.2);
  glVertex3f( 0.25, 0.3, -0.1);
  glVertex3f( -0.25, 0.3, -0.1);
  glVertex3f( -0.25, 0.15, -0.2);
  glEnd();

  //Atap mobil
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f( 0.25, 0.3, -0.1);
  glVertex3f( 0.25, 0.3, 0.5);
  glVertex3f( -0.25, 0.3, 0.5);
  glVertex3f( -0.25, 0.3, -0.1);
  glEnd();

  //Kap Belakang
  glBegin(GL_POLYGON);
  glVertex3f( 0.25, 0.3, 0.5);
  glVertex3f( 0.25, 0.0, 0.5);
  glVertex3f( -0.25, 0.0, 0.5);
  glVertex3f( -0.25, 0.3, 0.5);
  glEnd();

  //Penutup samping kiri kap
  glBegin(GL_POLYGON);
  //glColor3f(0.0, 1.0, 1.0);
  glVertex3f( 0.25, 0.0, -0.5);
  glVertex3f( 0.25, 0.1, -0.5);
  glVertex3f( 0.25, 0.15, -0.2);
  glVertex3f( 0.25, 0.0, -0.2);
  //glVertex3f( 0.25, 0.1, -0.2);
  //glVertex3f( 0.25, 0.3, -0.1);
  glEnd();

  //Penutup samping kanan kap
  glBegin(GL_POLYGON);
  glVertex3f( -0.25, 0.0, -0.5);
  glVertex3f( -0.25, 0.1, -0.5);
  glVertex3f( -0.25, 0.15, -0.2);
  glVertex3f( -0.25, 0.0, -0.2);
  glEnd();

  //penutup body samping kanan
  glBegin(GL_POLYGON);
  glVertex3f( -0.25, 0.0, 0.5);
  glVertex3f( -0.25, 0.0, -0.2);
  glVertex3f( -0.25, 0.15, -0.2);
  glVertex3f( -0.25, 0.15, 0.5);
  glEnd();

  //penutup body samping kiri
  glBegin(GL_POLYGON);
  glVertex3f( 0.25, 0.0, 0.5);
  glVertex3f( 0.25, 0.0, -0.2);
  glVertex3f( 0.25, 0.15, -0.2);
  glVertex3f( 0.25, 0.15, 0.5);
  glEnd();

  //jendela kanan
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 0.0);
  glVertex3f( -0.25, 0.15, -0.2);
  glVertex3f( -0.25, 0.3, -0.1);
  glVertex3f( -0.25, 0.3, 0.5);
  glVertex3f( -0.25, 0.15, 0.5);
  glEnd();


  //jendela kiri
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 0.0);
  glVertex3f( 0.25, 0.15, -0.2);
  glVertex3f( 0.25, 0.3, -0.1);
  glVertex3f( 0.25, 0.3, 0.5);
  glVertex3f( 0.25, 0.15, 0.5);
  glEnd();

  DrawCylinder(0.1, 0.1, 0.1);
  drawCircle(0.1,0.1, 0.2,0.1);
  glFlush();
  glutSwapBuffers();


 
}
 
//Callback Function
 
void Keys( int key, int x, int y ) 
{
 
  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    yrot += 10;
 
  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    yrot -= 10;
 
  else if (key == GLUT_KEY_UP)
    xrot += 10;
 
  else if (key == GLUT_KEY_DOWN)
    xrot -= 10;
  
  else if (key == GLUT_KEY_F1)
  {
    fullscreen = !fullscreen;
     
    if (fullscreen)
      glutFullScreen();
    else
    {
      glutReshapeWindow(500, 500);
      glutPositionWindow(50, 50);
    }
  } 
 
  //  Request display update
  glutPostRedisplay();
 
}

 
void idle()
{
if (!mouseDown)
{
xrot += 0.3f;
yrot += 0.4f;
}
 
glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
switch(key)
{
case 27 : 
exit(1); break;
}
}
 
void mouse( int button, int state, int x, int y)
{
    if (button == 3 || button == 4) {
        if (state == GLUT_UP) return;
        if (button == 3 ) {
          zoom -= 0.1;
        } else if(button == 4) {
          zoom += 0.1;
        }

    }
  else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    mouseDown = true;
     
    xdiff = x - yrot;
    ydiff = -y + xrot;
  }
  else
    mouseDown = false;

  glutPostRedisplay();
 
}
 
void mouseMotion(int x, int y)
{
  if (mouseDown)
  {
    yrot = x - xdiff;
    xrot = y + ydiff;
     
    glutPostRedisplay();
  }
}
 
void reshape (int w, int h)       
{
    glViewport (0,0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    //gluPerspective(45.0, GLfloat(w) / GLfloat(h), 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
 
}
// main() function
 
int main(int argc, char* argv[])
{
  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
 
  //  Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Set the width and height of the window 
  glutInitWindowSize(500, 500);
 
  // Set the position of the window 
  glutInitWindowPosition (100, 100);
 
  // Create window
  glutCreateWindow("Kijang Talun");
 
  //  Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(Keys);
  // Callback functions
 //glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(Keys);
  glutMotionFunc(mouseMotion);
  glutMouseFunc(mouse);
  //glutMouseWheelFunc(MouseWheel);
 
  if (!init())
  return 1;
  //Pass control to GLUT for events
  glutMainLoop();
  
 
  //  Return to OS
  return 0;
 
}