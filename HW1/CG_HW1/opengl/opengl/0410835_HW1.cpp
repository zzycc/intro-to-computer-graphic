#include "glut.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>

using namespace std;

void display();
void reshape(int _width, int _height);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void passiveMouseMotion(int x, int y);
void idle();
void lighting();
void drawSolidSphere(float R, int slice, int stack);

int width = 400, height = 400;
float Degree = 0.0f;
float Radius = 1.0f;
float Pi = 3.14159265358979323846f;
//Sun Spec
int Sun_Slice = 240;
int Sun_Stack = 60;
//Earth Spec
int Earth_Slice = 360;
int Earth_Stack = 180;
//Moon Spec
int Moon_Slice = 240;
int Moon_Stack = 60;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("0410835_HW1");
	//set light
	lighting();

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
	float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float yellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	//ModelView Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 50.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, width / (GLfloat)height, 0.1, 1000);
	//Viewport Matrix
	glViewport(0, 0, width, height);

	//
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Sun
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	drawSolidSphere(6 * Radius, Sun_Slice, Sun_Stack);
	//glutSolidSphere(6 * Radius,Sun_Slice,Sun_Stack);
	//Earth
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	glPushMatrix();
	glRotatef(Degree/365.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(20.0f, 0.0f, 0.0f);
	glRotatef(Degree / 365.0f, 0.0f, -1.0f, 0.0f);
	glRotatef(Degree, -sin(23.5/180*Pi), cos(23.5/180*Pi), 0.0f);
	glRotatef(23.5f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 10*Radius, 0.0f);
	glVertex3f(0.0f, -10*Radius, 0.0f);
	glEnd();
	drawSolidSphere(2 * Radius, Earth_Slice, Earth_Stack);
	//glutSolidSphere(2 * Radius, Earth_Slice, Earth_Stack);
	glPopMatrix();
	//Moon
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	glPushMatrix();
	glRotatef(Degree / 365.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(20.0f, 0.0f, 0.0f);
	glRotatef(Degree / 365.0f, 0.0f, -1.0f, 0.0f);
	glRotatef(23.5f, 0.0f, 0.0f, 1.0f);
	glRotatef(Degree / 28.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(3.0f, 0.0f, 0.0f);
	glRotatef(Degree / 28.0f, 0.0f, -1.0f, 0.0f);
	glRotatef(Degree / 28.0f, 0.0f, 1.0f, 0.0f);
	drawSolidSphere(Radius, Moon_Slice, Moon_Stack);
	//glutSolidSphere(Radius, Moon_Slice, Moon_Stack);
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
	case 'o':
	case 'O':
		if (Earth_Slice == 360) {
			Earth_Slice = 4;
			Earth_Stack = 2;
		}
		else {
			Earth_Slice = 360;
			Earth_Stack = 180;
		}
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
	Sleep(1);
	Degree = (Degree + 100);
	glutPostRedisplay();
}

void lighting()
{
	// enable lighting
	glEnable(GL_LIGHTING);
	//Add directed light
	GLfloat diffuse_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambient_color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 0.0f, 10.0f, 0.0f, 1.0f};
	glEnable(GL_LIGHT0);								//open light0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);	//set diffuse color of light0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);	//set ambient color of light0
	glLightfv(GL_LIGHT0, GL_POSITION, position);		//set position of light 0
}

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