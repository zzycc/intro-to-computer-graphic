#include "glut.h"
#include <iostream>

using namespace std;

void display();
void reshape(int _width, int _height);
void idle();
void lighting();

int width = 400, height = 400;
int degree = 0;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("WindowName");

	//set light
	lighting();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
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
	glEnable(GL_CULL_FACE);		//remove back face
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);		//normalized normal 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	glPushMatrix();
	glRotatef(degree, 0, 1, 0);
	glTranslatef(2.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glNormal3d(1, 1, 1);
	glVertex3f(1, 0, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	glNormal3d(1, 1, 1);
	glVertex3f(0, 1, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	glNormal3d(1, 1, 1);
	glVertex3f(0, 0, 1);
	glEnd();
	glPopMatrix();

	glutSolidSphere(1, 18, 18);

	glutSwapBuffers();
}

void reshape(int _width, int _height) {
	width = _width;
	height = _height;
}

void idle() {
	degree = (degree + 1) % 360;
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
}