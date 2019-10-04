/*
#include "glut.h"
#include <Windows.h>
#include <math.h>
#include <stdio.h>
void display();
void idle();
void lighting();
int width = 400, height = 400;
int Degree = 0;
float Pi = 3.14159265358979323846f;
void drawSolidSphere(float R, int slice, int stack) {//¸g«× ½n«×
	if (slice < 2 || stack < 2)
		return;
	for (int i = 0; i < stack; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= slice; j++) {
			float f_i = (float)i, f_j = (float)j, f_stack = (float)stack, f_slice = (float)slice;
			glNormal3f(R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos((f_i / f_stack)*Pi));
			glVertex3f(R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos((f_i / f_stack)*Pi));
			glNormal3f(R*sin((f_i + 1) / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin((f_i + 1) / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos(((f_i + 1) / f_stack)*Pi));
			glVertex3f(R*sin((f_i + 1) / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin((f_i + 1) / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos(((f_i + 1) / f_stack)*Pi));
		}
		glEnd();
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("WindowName");
	lighting();
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

void display()
{
	float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, width / (GLfloat)height, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluLookAt(10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	//gluLookAt(0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, .0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(Degree,0.0f,0.0f,1.0f);
	//glutSolidSphere(2,4,2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	drawSolidSphere(2, 4, 2);
	glPopMatrix();

	glutSwapBuffers();
}
void idle() {
	Sleep(20);
	Degree = (Degree + 1);
	glutPostRedisplay();
}
void lighting()
{
	// enable lighting
	glEnable(GL_LIGHTING);
	//Add directed light
	GLfloat diffuse_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambient_color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glEnable(GL_LIGHT0);								//open light0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);	//set diffuse color of light0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);	//set ambient color of light0
	glLightfv(GL_LIGHT0, GL_POSITION, position);		//set position of light 0
}*/