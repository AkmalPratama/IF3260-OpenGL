#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
bool fullscreen = false;
bool mouseDown = false;
void MouseWheel();
 
float xrot = 0.0f;
float yrot = 0.0f;
static double zoom=0.5;
 
float xdiff = 0.0f;
float ydiff = 0.0f;
 
void drawBox()
{
  glBegin(GL_POLYGON);
 
  glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
  glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
  glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
  glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 is purple
 
  glEnd();
 
  // White side - BACK
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f(  0.5, -0.5, 0.5 );
  glVertex3f(  0.5,  0.5, 0.5 );
  glVertex3f( -0.5,  0.5, 0.5 );
  glVertex3f( -0.5, -0.5, 0.5 );
  glEnd();
 
  // Purple side - RIGHT
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  0.0,  1.0 );
  glVertex3f( 0.5, -0.5, -0.5 );
  glVertex3f( 0.5,  0.5, -0.5 );
  glVertex3f( 0.5,  0.5,  0.5 );
  glVertex3f( 0.5, -0.5,  0.5 );
  glEnd();
 
  // Green side - LEFT
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();


  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  0.5, -0.5, -0.5 );
  glVertex3f(  0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
 
  // Blue side - TOP
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  0.5,  0.5,  0.5 );
  glVertex3f(  0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glEnd();

}
 
bool init()
{
glClearColor(0.93f, 0.93f, 0.93f, 0.0f);
 
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_EQUAL);
glClearDepth(1.0f);
 
return true;
}
 
void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
 
gluLookAt(
0.0f, 0.0f, 3.0f,
0.0f, 0.0f, 0.0f,
0.0f, 1.0f, 0.0f);
 
glRotatef(xrot, 1.0f, 0.0f, 0.0f);
glRotatef(yrot, 0.0f, 1.0f, 0.0f);
glScalef(zoom, zoom, zoom);
 
drawBox();
 
glFlush();
glutSwapBuffers();
}
 
void resize(int w, int h)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
 
glViewport(0, 0, w, h);
 
gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
 
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
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
 
void specialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
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
}
 
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

void mouse(int button, int state, int x, int y)
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
 
int main(int argc, char *argv[])
{
glutInit(&argc, argv);
 
glutInitWindowPosition(50, 50);
glutInitWindowSize(500, 500);
 
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
glEnable(GL_DEPTH_TEST);
glutCreateWindow("13 - Solid Shapes");
glutDisplayFunc(display);
glutKeyboardFunc(keyboard);
//glutSpecialFunc(specialKeyboard);
glutSpecialFunc(Keys);
glutMouseFunc(mouse);
glutMotionFunc(mouseMotion);
glutReshapeFunc(resize);
//glutIdleFunc(idle);
 
if (!init())
return 1;
 
glutMainLoop();
 
return 0;
}