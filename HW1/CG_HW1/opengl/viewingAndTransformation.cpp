/*
#include "glut.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

void display();
void reshape(int _width, int _height);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void passiveMouseMotion(int x, int y);
void idle();

void drawCircle();
int width = 400, height = 400;
int degree = 0;
int sl = 20;


const int n = 100;

float R = 0.5;

float Pi = 3.1415926;
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("WindowName");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}

void display()
{
	//ModelView Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 10.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, width / (GLfloat)height, 0.1, 1000);
	//Viewport Matrix
	glViewport(0, 0, width, height);

	//
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//sum
	//glutWireSphere(1, 18, 18);
	//plant1
	glPushMatrix();
	glRotatef(degree, 0.0f, 1.0f, 0.0f);
	glTranslatef(3.0, 0.0, 0.0);
	glRotatef(degree, 0.0f, 1.0f, 0.0f);
	glScalef(0.5, 0.5, 0.5);
	glutWireCube(1);
	glPopMatrix();
	//plant2
	glPushMatrix();
	glRotatef(degree * 2, 0.0f, 1.0f, 0.0f);
	glTranslatef(2.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	//Circle
	glPushMatrix();
	glRotatef(degree, 0.0f, 1.0f, 0.0f);
	glTranslatef(3.0, 0.0, 0.0);
	glRotatef(degree, 0.0f, 1.0f,0.0f);
	drawCircle();
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int _width, int _height) {
	width = _width;
	height = _height;
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'p':
	case 'P':
		system("pause");
		break; 
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y) {
}

void mouseMotion(int x, int y) {
}

void passiveMouseMotion(int x, int y) {
}

void idle() {
	Sleep(sl);
	degree = (degree + 1) % 360;
	glutPostRedisplay();
}

void drawCircle() {
	glBegin(GL_LINE_LOOP); //ø�s�覡

	//glColor3f(1.0, .0, .0); //�]�m�C��A3f�N��ѼƬ��T�ӯB�I��

	for (int i = 0; i < n; i++)

		glVertex3f(R*cos(2 * Pi / n * i),0, R*sin(2 * Pi / n * i));//�p�⧤��

	glEnd();
}
*/