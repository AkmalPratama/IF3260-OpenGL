#include <Windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define window_width  1080  
#define window_height 720 
#define PI 3.1415926f

GLfloat angle = 45.0f;
int refreshmill = 1;

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refreshmill, timer, 0);
}

void DrawBanDalam(float cx, float cy, float r, int num_segments) {
	//glLoadIdentity();
	//glTranslatef(0, 0, -10);
	glColor3ub(255, 0, 0);
	
	glBegin(GL_LINE_LOOP);
	glVertex2f(cx, cy - r);
	glVertex2f(cx, cy + r);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(cx - r, cy);
	glVertex2f(cx + r, cy);
	glEnd();

	glColor3ub(255, 255, 255);
	glBegin(GL_TRIANGLE_FAN);
	int x = 0, y = 0;
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * PI * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

/*void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.5f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3ub(0, 255, 0);
	glVertex2f(0.3f, 0.3f);
	glVertex2f(-0.3f, 0.3f);
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
	angle += 0.2;
}*/
void DrawBanLuar(float cx, float cy, float r, int num_segments) {
	glLoadIdentity();
	glTranslatef(0, 0, -10);
	glColor3ub(0, 255, 0);
	glBegin(GL_TRIANGLE_FAN);
	int x = 0, y = 0;
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * PI * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glLoadIdentity();
	if (width >= height) {
		gluOrtho2D(-1.0*aspect, 1.0*aspect, -1.0, 1.0);
	}
	else {
		gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
	}
}

void DrawBodyMobil() {
	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(3, 1);
	glVertex2f(-4, 1);
	glVertex2f(-4, 0);
	glVertex2f(3, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(100, 0, 255);
	glVertex2f(0, 2);
	glVertex2f(-4, 1);
	glVertex2f(-4, 0);
	glVertex2f(3, 0);
	glEnd();

}



void main_loop_function() {
	int c;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-2, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(2, 0.0f, 0.0f);
	DrawBanDalam(-2, 0, 0.4, 40);
	DrawBanLuar(-2, 0, 0.7, 40);
	glPopMatrix();
	angle += 0.1;

	glTranslatef(1, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-1, 0.0f, 0.0f);
	DrawBanDalam(1, 0, 0.4, 40);
	DrawBanLuar(1, 0, 0.7, 40);
	glPopMatrix();
	angle += 0.1;
	DrawBodyMobil();
	glutSwapBuffers();
	// c = getchar();
}
void GL_Setup(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45, (float)width / height, .1, 100);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(50, 50);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Mobil Mantab");
	//glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	//glutTimerFunc(0, timer, 0);
	glutIdleFunc(main_loop_function);
	GL_Setup(window_width, window_height);
	glutMainLoop();
}